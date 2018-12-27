/*
   Copyright (C) 2015-2019 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "sendvcardsjob.h"

#include <AkonadiCore/Item>
#include <AkonadiCore/ItemFetchJob>
#include <AkonadiCore/ItemFetchScope>
#include <Akonadi/Contact/ContactGroupExpandJob>
#include "MimeTreeParser/AttachmentTemporaryFilesDirs"
#include "kaddressbook_sendvcardsplugin_debug.h"
#include <QTemporaryDir>
#include <QFile>
#include <KLocalizedString>
#include <KToolInvocation>

using namespace KABSendVCards;

SendVcardsJob::SendVcardsJob(const Akonadi::Item::List &listItem, QObject *parent)
    : QObject(parent)
    , mListItem(listItem)
{
    //Don't delete it.
    mAttachmentTemporary = new MimeTreeParser::AttachmentTemporaryFilesDirs();
}

SendVcardsJob::~SendVcardsJob()
{
    delete mTempDir;
    mTempDir = nullptr;
    //Don't delete it.
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

    for (const Akonadi::Item &item : qAsConst(mListItem)) {
        if (item.hasPayload<KContacts::Addressee>()) {
            const KContacts::Addressee contact = item.payload<KContacts::Addressee>();
            QByteArray data = item.payloadData();
            //Workaround about broken kaddressbook fields.
            KContacts::adaptIMAttributes(data);
            createTemporaryDir();
            const QString contactRealName(contact.realName());
            const QString attachmentName = (contactRealName.isEmpty() ? QStringLiteral("vcard") : contactRealName) + QStringLiteral(".vcf");
            createTemporaryFile(data, attachmentName);
        } else if (item.hasPayload<KContacts::ContactGroup>()) {
            ++mExpandGroupJobCount;
            const KContacts::ContactGroup group = item.payload<KContacts::ContactGroup>();
            const QString groupName(group.name());
            const QString attachmentName = (groupName.isEmpty() ? QStringLiteral("vcard") : groupName) + QStringLiteral(".vcf");
            Akonadi::ContactGroupExpandJob *expandJob = new Akonadi::ContactGroupExpandJob(group, this);
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
        mTempDir = new QTemporaryDir(QDir::tempPath() + QLatin1Char('/') +  QStringLiteral("sendvcards"));
        mTempDir->setAutoRemove(false);
        mAttachmentTemporary->addTempDir(mTempDir->path());
    }
}

void SendVcardsJob::jobFinished()
{
    const QStringList lstAttachment = mAttachmentTemporary->temporaryFiles();
    if (!lstAttachment.isEmpty()) {
        KToolInvocation::invokeMailer(QString(), QString(), QString(), QString(), QString(), QString(), lstAttachment);
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
    Akonadi::ContactGroupExpandJob *expandJob = qobject_cast<Akonadi::ContactGroupExpandJob *>(job);
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
