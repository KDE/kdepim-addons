/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "sendvcardsjob.h"

#include "kaddressbook_sendvcardsplugin_debug.h"
#include <Akonadi/ContactGroupExpandJob>
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <KEMailClientLauncherJob>
#include <KLocalizedString>
#include <MimeTreeParser/AttachmentTemporaryFilesDirs>
#include <QFile>
#include <QTemporaryDir>

using namespace KABSendVCards;

SendVcardsJob::SendVcardsJob(const Akonadi::Item::List &listItem, QObject *parent)
    : QObject(parent)
    , mListItem(listItem)
{
    // Don't delete it.
    mAttachmentTemporary = new MimeTreeParser::AttachmentTemporaryFilesDirs();
}

SendVcardsJob::~SendVcardsJob()
{
    delete mTempDir;
    mTempDir = nullptr;
    // Don't delete it.
    mAttachmentTemporary = nullptr;
}

bool SendVcardsJob::start()
{
    if (mListItem.isEmpty()) {
        qCDebug(KADDRESSBOOK_SENDVCARDS_LOG) << " No Item found";
        mAttachmentTemporary->deleteLater();
        mAttachmentTemporary = nullptr;
        deleteLater();
        return false;
    }

    for (const Akonadi::Item &item : std::as_const(mListItem)) {
        if (item.hasPayload<KContacts::Addressee>()) {
            const auto contact = item.payload<KContacts::Addressee>();
            QByteArray data = item.payloadData();
            // Workaround about broken kaddressbook fields.
            KContacts::adaptIMAttributes(data);
            createTemporaryDir();
            const QString contactRealName(contact.realName());
            const QString attachmentName = (contactRealName.isEmpty() ? QStringLiteral("vcard") : contactRealName) + QStringLiteral(".vcf");
            createTemporaryFile(data, attachmentName);
        } else if (item.hasPayload<KContacts::ContactGroup>()) {
            ++mExpandGroupJobCount;
            const auto group = item.payload<KContacts::ContactGroup>();
            const QString groupName(group.name());
            const QString attachmentName = (groupName.isEmpty() ? QStringLiteral("vcard") : groupName) + QStringLiteral(".vcf");
            auto expandJob = new Akonadi::ContactGroupExpandJob(group, this);
            expandJob->setProperty("groupName", attachmentName);
            connect(expandJob, &KJob::result, this, &SendVcardsJob::slotExpandGroupResult);
            expandJob->start();
        }
    }

    if (mExpandGroupJobCount == 0) {
        jobFinished();
    }
    return true;
}

void SendVcardsJob::createTemporaryDir()
{
    if (!mTempDir) {
        mTempDir = new QTemporaryDir(QDir::tempPath() + QLatin1Char('/') + QStringLiteral("sendvcards"));
        mTempDir->setAutoRemove(false);
        mAttachmentTemporary->addTempDir(mTempDir->path());
    }
}

void SendVcardsJob::jobFinished()
{
    const QStringList tempFilePaths{mAttachmentTemporary->temporaryFiles()};
    QList<QUrl> lstAttachment;
    for (const QString &path : tempFilePaths) {
        lstAttachment.append(QUrl::fromLocalFile(path));
    }
    if (!lstAttachment.isEmpty()) {
        auto job = new KEMailClientLauncherJob(this);
        job->setAttachments(lstAttachment);
        job->start();
    } else {
        Q_EMIT sendVCardsError(i18n("No vCard created."));
    }
    mAttachmentTemporary->removeTempFiles();
    deleteLater();
}

KContacts::VCardConverter::Version SendVcardsJob::version() const
{
    return mVersion;
}

void SendVcardsJob::setVersion(KContacts::VCardConverter::Version version)
{
    mVersion = version;
}

void SendVcardsJob::slotExpandGroupResult(KJob *job)
{
    auto expandJob = qobject_cast<Akonadi::ContactGroupExpandJob *>(job);
    Q_ASSERT(expandJob);

    const QString attachmentName = expandJob->property("groupName").toString();
    KContacts::VCardConverter converter;
    const QByteArray groupData = converter.exportVCards(expandJob->contacts(), mVersion);
    createTemporaryDir();
    createTemporaryFile(groupData, attachmentName);

    --mExpandGroupJobCount;
    if (mExpandGroupJobCount == 0) {
        jobFinished();
    }
}

void SendVcardsJob::createTemporaryFile(const QByteArray &data, const QString &filename)
{
    QFile file(mTempDir->path() + QLatin1Char('/') + filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCDebug(KADDRESSBOOK_SENDVCARDS_LOG) << "Cannot write vcard filename :" << filename;
        Q_EMIT sendVCardsError(i18n("Temporary file \'%1\' cannot be created", filename));
        return;
    }

    QTextStream out(&file);
    out << data;
    file.close();
    mAttachmentTemporary->addTempFile(file.fileName());
}
