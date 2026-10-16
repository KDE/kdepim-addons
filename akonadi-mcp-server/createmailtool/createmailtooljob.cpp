/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "createmailtooljob.h"
#include <Akonadi/Item>
#include <Akonadi/ItemCreateJob>
#include <Akonadi/MessageFlags>
#include <Akonadi/SpecialMailCollections>
#include <Akonadi/SpecialMailCollectionsRequestJob>
#include <KIdentityManagementCore/Identity>
#include <KIdentityManagementCore/IdentityManager>
#include <KJob>
#include <KLocalizedString>
#include <KMime/Message>
#include <QDateTime>

using namespace Qt::Literals::StringLiterals;

CreateMailToolJob::CreateMailToolJob(QObject *parent)
    : ToolJobBase{parent}
{
}

CreateMailToolJob::~CreateMailToolJob() = default;

void CreateMailToolJob::setSubject(const QString &subject)
{
    mSubject = subject;
}

void CreateMailToolJob::setTo(const QStringList &to)
{
    mTo = to;
}

void CreateMailToolJob::setCc(const QStringList &cc)
{
    mCc = cc;
}

void CreateMailToolJob::setBcc(const QStringList &bcc)
{
    mBcc = bcc;
}

void CreateMailToolJob::setBody(const QString &body)
{
    mBody = body;
}

bool CreateMailToolJob::canStart() const
{
    return ToolJobBase::canStart() && !mSubject.isEmpty();
}

QString CreateMailToolJob::invalidArgumentsMessage() const
{
    return i18n("Subject must be a non-empty string");
}

void CreateMailToolJob::startJob()
{
    auto requestJob = new Akonadi::SpecialMailCollectionsRequestJob(this);
    requestJob->requestDefaultCollection(Akonadi::SpecialMailCollections::Drafts);
    connect(requestJob, &KJob::result, this, &CreateMailToolJob::slotDraftsCollectionResult);
    setCurrentJob(requestJob);
}

void CreateMailToolJob::slotDraftsCollectionResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Drafts folder fetch failed: %1"))) {
        return;
    }
    const Akonadi::Collection collection = qobject_cast<Akonadi::SpecialMailCollectionsRequestJob *>(job)->collection();
    if (!collection.isValid()) {
        finish(i18n("No Drafts folder found"), true);
        return;
    }
    createMail(collection);
}

void CreateMailToolJob::createMail(const Akonadi::Collection &collection)
{
    auto message = std::make_shared<KMime::Message>();
    const KIdentityManagementCore::Identity &identity = KIdentityManagementCore::IdentityManager::self()->defaultIdentity();
    if (!identity.isNull()) {
        message->from()->fromUnicodeString(identity.fullEmailAddr());
        auto identityHeader = std::make_unique<KMime::Headers::Generic>("X-KMail-Identity");
        identityHeader->fromUnicodeString(QString::number(identity.uoid()));
        message->setHeader(std::move(identityHeader));
    }
    message->subject()->fromUnicodeString(mSubject);
    if (!mTo.isEmpty()) {
        message->to()->fromUnicodeString(mTo.join(u", "_s));
    }
    if (!mCc.isEmpty()) {
        message->cc()->fromUnicodeString(mCc.join(u", "_s));
    }
    if (!mBcc.isEmpty()) {
        message->bcc()->fromUnicodeString(mBcc.join(u", "_s));
    }
    message->date()->setDateTime(QDateTime::currentDateTime());
    message->contentType()->setMimeType("text/plain");
    message->contentType()->setCharset("utf-8");
    message->contentTransferEncoding()->setEncoding(KMime::Headers::CEquPr);
    message->setBody(mBody.toUtf8());
    message->assemble();

    Akonadi::Item item;
    item.setMimeType(KMime::Message::mimeType());
    item.setPayload<std::shared_ptr<KMime::Message>>(message);
    item.setFlag(Akonadi::MessageFlags::Seen);

    auto createJob = new Akonadi::ItemCreateJob(item, collection, this);
    createJob->setProperty("folderName", collection.displayName());
    connect(createJob, &KJob::result, this, &CreateMailToolJob::slotItemCreateResult);
    setCurrentJob(createJob);
}

void CreateMailToolJob::slotItemCreateResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Mail creation failed: %1"))) {
        return;
    }
    const Akonadi::Item item = qobject_cast<Akonadi::ItemCreateJob *>(job)->item();
    finish(i18n("Mail \"%1\" created in folder \"%2\" (item id: %3). It can be edited in KMail with edit_mail",
                mSubject,
                job->property("folderName").toString(),
                QString::number(item.id())));
}

#include "moc_createmailtooljob.cpp"
