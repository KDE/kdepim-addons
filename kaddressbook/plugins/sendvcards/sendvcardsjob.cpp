/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

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
using namespace Qt::Literals::StringLiterals;
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
    // Don't delete it immediately, it might still have pending work in queued connections
    if (mAttachmentTemporary) {
        mAttachmentTemporary->deleteLater();
        mAttachmentTemporary = nullptr;
    }
}

QString SendVcardsJob::createUniqueAttachmentName(const QString &contactRealName, const QStringList &existingVcard)
{
    QString newContactRealName = contactRealName;
    if (newContactRealName.isEmpty()) {
        newContactRealName = QStringLiteral("vcard");
    }
    if (existingVcard.contains(newContactRealName, Qt::CaseInsensitive)) {
        int index = 0;
        QString uniqueContactRealName = newContactRealName;
        do {
            index++;
            uniqueContactRealName = u"%1_%2"_s.arg(newContactRealName).arg(index);
        } while (existingVcard.contains(uniqueContactRealName));
        newContactRealName = uniqueContactRealName;
    }
    return newContactRealName;
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

    QStringList attachmentNameLst;
    for (const Akonadi::Item &item : std::as_const(mListItem)) {
        if (item.hasPayload<KContacts::Addressee>()) {
            const auto contact = item.payload<KContacts::Addressee>();
            QByteArray data = item.payloadData();
            // Workaround about broken kaddressbook fields.
            KContacts::adaptIMAttributes(data);
            createTemporaryDir();
            const QString contactRealName(contact.realName());
            const QString generatedUniqueAttachmentName = createUniqueAttachmentName(contactRealName, attachmentNameLst);
            const QString attachmentName = generatedUniqueAttachmentName + QStringLiteral(".vcf");
            attachmentNameLst.append(generatedUniqueAttachmentName);
            createTemporaryFile(data, attachmentName);
        } else if (item.hasPayload<KContacts::ContactGroup>()) {
            ++mExpandGroupJobCount;
            const auto group = item.payload<KContacts::ContactGroup>();
            const QString uniqueName = createUniqueAttachmentName(group.name(), attachmentNameLst);
            attachmentNameLst.append(uniqueName);
            auto expandJob = new Akonadi::ContactGroupExpandJob(group, this);
            const QString attachmentName = uniqueName + QStringLiteral(".vcf");
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
    if (!file.open(QIODevice::WriteOnly)) {
        qCDebug(KADDRESSBOOK_SENDVCARDS_LOG) << "Cannot write vcard filename :" << filename;
        Q_EMIT sendVCardsError(i18n("Temporary file \'%1\' cannot be created", filename));
        return;
    }

    QTextStream out(&file);
    out << data;
    file.close();
    mAttachmentTemporary->addTempFile(file.fileName());
}

#include "moc_sendvcardsjob.cpp"
