/*
  This file is part of KOrganizer.
  SPDX-FileCopyrightText: 2001 Cornelius Schumacher <schumacher@kde.org>
  SPDX-FileCopyrightText: 2007 Loïc Corbasson <loic.corbasson@gmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "picoftheday.h"
#include "configdialog.h"

#include "korganizer_picoftheday_plugin_debug.h"
#include <KConfig>
#include <KConfigGroup>
#include <KIO/Scheduler>
#include <KLocalizedString>

#include <QDomDocument>
// https://www.mediawiki.org/wiki/API:Picture_of_the_day_viewer
Picoftheday::Picoftheday()
{
    KConfig _config(QStringLiteral("korganizerrc"));
    KConfigGroup config(&_config, "Picture of the Day Plugin");
    mThumbSize = config.readEntry("InitialThumbnailSize", QSize(120, 60));
}

Picoftheday::~Picoftheday()
{
}

void Picoftheday::configure(QWidget *parent)
{
    ConfigDialog dlg(parent);
    dlg.exec();
}

QString Picoftheday::info() const
{
    return i18n(
        "<qt>This plugin provides the Wikipedia "
        "<i>Picture of the Day</i>.</qt>");
}

Element::List Picoftheday::createDayElements(const QDate &date)
{
    Element::List elements;

    auto element = new POTDElement(QStringLiteral("main element"), date, mThumbSize);
    elements.append(element);

    return elements;
}

////////////////////////////////////////////////////////////////////////////////

POTDElement::POTDElement(const QString &id, QDate date, QSize initialThumbSize)
    : StoredElement(id)
    , mDate(date)
    , mThumbSize(initialThumbSize)
{
    setShortText(i18n("Loading..."));
    setLongText(i18n("<qt>Loading <i>Picture of the Day</i>...</qt>"));

    mTimer = new QTimer(this);
    mTimer->setSingleShot(true);

    step1StartDownload();
}

/** First step of three in the download process */
void POTDElement::step1StartDownload()
{
    // Start downloading the picture
    if (!mFirstStepCompleted && !mFirstStepJob) {
        QUrl url = QUrl(QStringLiteral("https://en.wikipedia.org/w/index.php?title=Template:POTD_protected/") + mDate.toString(Qt::ISODate)
                        + QStringLiteral("&action=raw"));

        // The file at that URL contains the file name for the POTD
        qCWarning(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "step1StartDownload url :" << url;

        mFirstStepJob = KIO::storedGet(url, KIO::NoReload, KIO::HideProgressInfo);
        KIO::Scheduler::setJobPriority(mFirstStepJob, 1);

        connect(mFirstStepJob, &KIO::SimpleJob::result, this, &POTDElement::step1Result);
        connect(this, &POTDElement::step1Success, this, &POTDElement::step2GetImagePage);
    }
}

/**
  Give it a job which fetched the raw page,
  and it'll give you the image file name hiding in it.
 */
void POTDElement::step1Result(KJob *job)
{
    if (job->error()) {
        qCWarning(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "POTD:" << mDate << ": could not get POTD file name:" << job->errorString();
        qCDebug(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "POTD:" << mDate << ": file name:" << mFileName;
        qCDebug(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "POTD:" << mDate << ": full-size image:" << mFullSizeImageUrl;
        qCDebug(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "POTD:" << mDate << ": thumbnail:" << mThumbUrl;
        mFirstStepCompleted = false;
        return;
    }

    // First step completed: we now know the POTD's file name
    auto const transferJob = static_cast<KIO::StoredTransferJob *>(job);
    const QStringList lines = QString::fromUtf8(transferJob->data().data(), transferJob->data().size()).split(QLatin1Char('\n'));

    for (const QString &line : lines) {
        if (line.startsWith(QLatin1String("|image="))) {
            mFileName = line;
            break;
        }
    }
    mFileName.remove(QStringLiteral("|image=")).replace(QLatin1Char(' '), QLatin1Char('_'));

    for (const QString &line : lines) {
        if (line.startsWith(QLatin1String("|texttitle="))) {
            mDescription = line;
            break;
        }
    }
    mDescription.remove(QStringLiteral("|texttitle="));
    if (!mDescription.isEmpty()) {
        mLongText = mDescription;
    } else {
        mLongText = mFileName;
    }
    mLongText = i18n("Wikipedia POTD: %1", mLongText);
    Q_EMIT gotNewLongText(mLongText);

    qCDebug(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "FILENAME=" << mFileName;
    qCDebug(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "DESCRIPTION=" << mDescription;

    mFirstStepCompleted = true;
    mFirstStepJob = nullptr;
    Q_EMIT step1Success();
}

/** Second step of three in the download process */
void POTDElement::step2GetImagePage()
{
    if (!mSecondStepCompleted && !mSecondStepJob) {
        mUrl = QUrl(QLatin1String("https://en.wikipedia.org/wiki/File:") + mFileName);
        // We'll find the info to get the thumbnail we want on the POTD's image page

        Q_EMIT gotNewUrl(mUrl);
        mShortText = i18n("Picture Page");
        Q_EMIT gotNewShortText(mShortText);

        mSecondStepJob = KIO::storedGet(mUrl, KIO::NoReload, KIO::HideProgressInfo);
        KIO::Scheduler::setJobPriority(mSecondStepJob, 1);

        connect(mSecondStepJob, &KIO::SimpleJob::result, this, &POTDElement::step2Result);
        connect(this, &POTDElement::step2Success, this, &POTDElement::step3GetThumbnail);
    }
}

/**
  Give it a job which fetched the image page,
  and it'll give you the appropriate thumbnail URL.
 */
void POTDElement::step2Result(KJob *job)
{
    if (job->error()) {
        qCWarning(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "POTD:" << mDate << ": could not get POTD image page:" << job->errorString();
        qCDebug(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "POTD:" << mDate << ": file name:" << mFileName;
        qCDebug(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "POTD:" << mDate << ": full-size image:" << mFullSizeImageUrl;
        qCDebug(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "POTD:" << mDate << ": thumbnail:" << mThumbUrl;
        mSecondStepCompleted = false;
        return;
    }

    // Get the image URL from the image page's source code
    // and transform it to get an appropriate thumbnail size
    auto const transferJob = static_cast<KIO::StoredTransferJob *>(job);

    QDomDocument imgPage;
    if (!imgPage.setContent(QString::fromUtf8(transferJob->data().data(), transferJob->data().size()))) {
        qCWarning(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "POTD:" << mDate << ": Wikipedia returned an invalid XML page for image" << mFileName;
        return;
    }

    // We go through all links and stop at the first right-looking candidate
    QDomNodeList links = imgPage.elementsByTagName(QStringLiteral("a"));
    for (int i = 0; i < links.length(); ++i) {
        QString href = links.item(i).attributes().namedItem(QStringLiteral("href")).nodeValue();
        if (href.startsWith(QStringLiteral("//upload.wikimedia.org/wikipedia/commons/"))) {
            mFullSizeImageUrl = QUrl(href);
            mFullSizeImageUrl.setScheme(QStringLiteral("https"));
            break;
        }
    }

    // We get the image's width/height ratio
    mHWRatio = 1.0;
    QDomNodeList images = imgPage.elementsByTagName(QStringLiteral("img"));
    for (int i = 0; i < links.length(); ++i) {
        QDomNamedNodeMap attr = images.item(i).attributes();
        QString src = attr.namedItem(QStringLiteral("src")).nodeValue();

        if (src.startsWith(thumbnailUrl(mFullSizeImageUrl).url())) {
            if ((attr.namedItem(QStringLiteral("height")).nodeValue().toInt() != 0) && (attr.namedItem(QStringLiteral("width")).nodeValue().toInt() != 0)) {
                mHWRatio = attr.namedItem(QStringLiteral("height")).nodeValue().toFloat() / attr.namedItem(QStringLiteral("width")).nodeValue().toFloat();
            }
            break;
        }
    }
    qCDebug(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "POTD:" << mDate << ": h/w ratio:" << mHWRatio;
    qCDebug(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "POTD:" << mDate << ": got POTD image page source:" << mFullSizeImageUrl;

    if (!mFullSizeImageUrl.isEmpty()) {
        mSecondStepCompleted = true;
        mSecondStepJob = nullptr;
        Q_EMIT step2Success();
    }
}

QUrl POTDElement::thumbnailUrl(const QUrl &fullSizeUrl, const int width) const
{
    QString thumbUrl = fullSizeUrl.url();
    if (width != 0) {
        thumbUrl.replace(QRegExp(QLatin1String("//upload.wikimedia.org/wikipedia/commons/(.*)/([^/]*)")),
                         QStringLiteral("//upload.wikimedia.org/wikipedia/commons/thumb/\\1/\\2/") + QString::number(width) + QStringLiteral("px-\\2"));
    } else { // This will not return a valid thumbnail URL, but will at least
        // give some info (the beginning of the URL)
        thumbUrl.replace(QRegExp(QLatin1String("//upload.wikimedia.org/wikipedia/commons/(.*)/([^/]*)")),
                         QStringLiteral("//upload.wikimedia.org/wikipedia/commons/thumb/\\1/\\2"));
    }
    thumbUrl.replace(QRegExp(QLatin1String("^file:////")), QStringLiteral("https://"));
    return QUrl(thumbUrl);
}

/** Third step of three in the downloading process */
void POTDElement::step3GetThumbnail()
{
    if (mThirdStepJob) {
        mThirdStepJob->kill();
    }
    mThirdStepJob = nullptr;

    int thumbWidth = mThumbSize.width();
    int thumbHeight = static_cast<int>(thumbWidth * mHWRatio);
    if (mThumbSize.height() < thumbHeight) {
        /* if the requested height is less than the requested width * ratio
           we would download too much, as the downloaded picture would be
           taller than requested, so we adjust the width of the picture to
           be downloaded in consequence */
        thumbWidth /= (thumbHeight / mThumbSize.height());
        thumbHeight = static_cast<int>(thumbWidth * mHWRatio);
    }
    mDlThumbSize = QSize(thumbWidth, thumbHeight);
    qCDebug(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "POTD:" << mDate << ": will download thumbnail of size" << mDlThumbSize;
    mThumbUrl = thumbnailUrl(mFullSizeImageUrl, thumbWidth);

    qCDebug(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "POTD:" << mDate << ": got POTD thumbnail URL:" << mThumbUrl;

    mThirdStepJob = KIO::storedGet(mThumbUrl, KIO::NoReload, KIO::HideProgressInfo);
    KIO::Scheduler::setJobPriority(mThirdStepJob, 1);

    connect(mThirdStepJob, &KIO::SimpleJob::result, this, &POTDElement::step3Result);
}

/**
  Give it a job which fetched the thumbnail,
  and it'll give the corresponding pixmap to you.
 */
void POTDElement::step3Result(KJob *job)
{
    if (job != mThirdStepJob) {
        return;
    }
    mThirdStepJob = nullptr;

    if (job->error()) {
        qCWarning(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "POTD:" << mDate << ": could not get POTD:" << job->errorString();
        qCDebug(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "POTD:" << mDate << ": file name:" << mFileName;
        qCDebug(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "POTD:" << mDate << ": full-size image:" << mFullSizeImageUrl;
        qCDebug(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "POTD:" << mDate << ": thumbnail:" << mThumbUrl;
        return;
    }

    // Last step completed: we get the pixmap from the transfer job's data
    auto const transferJob = static_cast<KIO::StoredTransferJob *>(job);
    if (mPixmap.loadFromData(transferJob->data())) {
        qCDebug(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "POTD:" << mDate << ": got POTD.";
        Q_EMIT gotNewPixmap(mPixmap.scaled(mThumbSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

QPixmap POTDElement::newPixmap(const QSize &size)
{
    if ((mThumbSize.width() < size.width()) || (mThumbSize.height() < size.height())) {
        qCDebug(KORGANIZERPICOFTHEDAYPLUGIN_LOG) << "POTD:" << mDate << ": called for a new pixmap size (" << size << "instead of" << mThumbSize
                                                 << ", stored pixmap:" << mPixmap.size() << ")";
        setThumbnailSize(size);

        if (!mFirstStepCompleted) {
            step1StartDownload(); // First run, start from the beginning
        } else if ((mDlThumbSize.width() < size.width()) && (mDlThumbSize.height() < size.height())) {
            if (mThirdStepJob) {
                // Another download (for the old size) is already running;
                // we'll run after that
                disconnect(this, &POTDElement::step3Success, this, &POTDElement::step3GetThumbnail);
                connect(this, &POTDElement::step3Success, this, &POTDElement::step3GetThumbnail);
            } else if (mFirstStepJob || mSecondStepJob) {
                // The download process did not get to step 3 yet, and will download
                // the correct size automagically
            } else {
                // We start a new thumbnail download a little later; the following code
                // is to avoid too frequent transfers e.g. when resizing
                mTimer->stop();
                disconnect(mTimer, &QTimer::timeout, this, &POTDElement::step3GetThumbnail);
                connect(mTimer, &QTimer::timeout, this, &POTDElement::step3GetThumbnail);
                mTimer->setSingleShot(true);
                mTimer->start(1000);
            }
        }
    }

    /* else, either we already got a sufficiently big pixmap (stored in mPixmap),
       or we will get one anytime soon (we are downloading it already) and we will
       actualize what we return here later via gotNewPixmap */
    if (mPixmap.isNull()) {
        return QPixmap();
    }
    return mPixmap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void POTDElement::setThumbnailSize(QSize size)
{
    mThumbSize = size;
}
