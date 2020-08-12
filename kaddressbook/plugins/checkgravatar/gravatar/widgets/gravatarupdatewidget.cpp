/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "gravatarupdatewidget.h"

#include <QGridLayout>
#include <KLocalizedString>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>

#include <Gravatar/GravatarResolvUrlJob>

#include <kio/transferjob.h>

using namespace KABGravatar;
GravatarUpdateWidget::GravatarUpdateWidget(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *hboxEmail = new QHBoxLayout;

    QLabel *lab = new QLabel(i18n("Email:"));
    lab->setObjectName(QStringLiteral("emaillabel"));
    hboxEmail->addWidget(lab);

    mEmailLab = new QLabel;
    mEmailLab->setObjectName(QStringLiteral("email"));
    hboxEmail->addWidget(mEmailLab);
    mainLayout->addLayout(hboxEmail, 0, 0);

    mSearchGravatar = new QPushButton(i18n("Search"));
    mSearchGravatar->setEnabled(false);
    mSearchGravatar->setObjectName(QStringLiteral("search"));
    mainLayout->addWidget(mSearchGravatar, 4, 0);
    connect(mSearchGravatar, &QAbstractButton::clicked, this, &GravatarUpdateWidget::slotSearchGravatar);
    mResultGravatar = new QLabel;
    QFont font = mResultGravatar->font();
    font.setBold(true);
    mResultGravatar->setFont(font);

    mResultGravatar->setObjectName(QStringLiteral("result"));
    mainLayout->addWidget(mResultGravatar, 0, 2, 4, 1, Qt::AlignCenter);
}

GravatarUpdateWidget::~GravatarUpdateWidget()
{
}

void GravatarUpdateWidget::setEmail(const QString &email)
{
    mEmail = email;
    mEmailLab->setText(mEmail);
    mResultGravatar->setText(QString());
    mSearchGravatar->setEnabled(!mEmail.trimmed().isEmpty());
}

QPixmap GravatarUpdateWidget::pixmap() const
{
    return mPixmap;
}

void GravatarUpdateWidget::setOriginalUrl(const QUrl &url)
{
    QImage image;
    QByteArray imageData;
    KIO::TransferJob *job = KIO::get(url, KIO::NoReload);
    QObject::connect(job, &KIO::TransferJob::data,
                     [&imageData](KIO::Job *, const QByteArray &data) {
        imageData.append(data);
    });
    if (job->exec()) {
        if (image.loadFromData(imageData)) {
            mResultGravatar->setPixmap(QPixmap::fromImage(image));
        }
    }
}

void GravatarUpdateWidget::setOriginalPixmap(const QPixmap &pix)
{
    if (!pix.isNull()) {
        mResultGravatar->setPixmap(pix);
    }
}

QUrl GravatarUpdateWidget::resolvedUrl() const
{
    return mCurrentUrl;
}

void GravatarUpdateWidget::slotSearchGravatar()
{
    mCurrentUrl.clear();
    if (!mEmail.isEmpty()) {
        Gravatar::GravatarResolvUrlJob *job = new Gravatar::GravatarResolvUrlJob(this);
        job->setEmail(mEmail);
        if (job->canStart()) {
            job->setUseDefaultPixmap(false);
            connect(job, &Gravatar::GravatarResolvUrlJob::finished, this, &GravatarUpdateWidget::slotSearchGravatarFinished);
            connect(job, &Gravatar::GravatarResolvUrlJob::resolvUrl, this, &GravatarUpdateWidget::slotResolvUrl);
            mSearchGravatar->setEnabled(false);
            Q_EMIT activateDialogButton(false);
            mPixmap = QPixmap();
            mCurrentUrl.clear();
            job->start();
        } else {
            mResultGravatar->setText(i18n("Search is impossible."));
            job->deleteLater();
        }
    }
}

void GravatarUpdateWidget::slotResolvUrl(const QUrl &url)
{
    mCurrentUrl = url;
}

void GravatarUpdateWidget::slotSearchGravatarFinished(Gravatar::GravatarResolvUrlJob *job)
{
    bool foundGravatar = false;
    if (job && job->hasGravatar()) {
        mPixmap = job->pixmap();
        mResultGravatar->setPixmap(mPixmap);
        foundGravatar = true;
    } else {
        mResultGravatar->setText(i18n("No Gravatar Found."));
    }
    Q_EMIT activateDialogButton(foundGravatar);
    mSearchGravatar->setEnabled(true);
}
