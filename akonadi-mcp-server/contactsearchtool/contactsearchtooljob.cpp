/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "contactsearchtooljob.h"
#include "akonadimcpprotocol_debug.h"
#include <Akonadi/ContactSearchJob>
#include <KJob>
#include <KLocalizedString>
#include <QDateTime>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>

using namespace Qt::Literals::StringLiterals;

ContactSearchToolJob::ContactSearchToolJob(QObject *parent)
    : QObject{parent}
{
}

ContactSearchToolJob::~ContactSearchToolJob() = default;

void ContactSearchToolJob::setNameOrEmail(const QString &str)
{
    mSearchString = str;
}

void ContactSearchToolJob::setFields(ContactFields fields)
{
    mFields = fields;
}

bool ContactSearchToolJob::canStart() const
{
    return !mSearchString.isEmpty() && mToolCall;
}

void ContactSearchToolJob::start()
{
    if (!canStart()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << "ContactSearchToolJob can't start";
        if (mToolCall) {
            mToolCall->finishWithText(i18n("Search string must be a non-empty string"), true);
        }
        deleteLater();
        return;
    }

    mSearchJob = new Akonadi::ContactSearchJob(this);
    mSearchJob->setQuery(Akonadi::ContactSearchJob::NameOrEmail, mSearchString, Akonadi::ContactSearchJob::ContainsMatch);
    connect(mSearchJob, &KJob::result, this, &ContactSearchToolJob::slotResult);
    connect(mToolCall, &TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall::cancelled, this, &ContactSearchToolJob::slotCancelled);
}

void ContactSearchToolJob::slotCancelled()
{
    if (mSearchJob) {
        mSearchJob->kill();
    }
    deleteLater();
}

void ContactSearchToolJob::setMcpProtocolServerToolCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    mToolCall = call;
}

void ContactSearchToolJob::slotResult(KJob *job)
{
    if (!mToolCall) {
        deleteLater();
        return;
    }
    if (job->error()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << "Contact search failed:" << job->errorString();
        mToolCall->finishWithText(i18n("Contact search failed: %1", job->errorString()), true);
        deleteLater();
        return;
    }
    const KContacts::Addressee::List contacts = qobject_cast<Akonadi::ContactSearchJob *>(job)->contacts();
    if (contacts.isEmpty()) {
        mToolCall->finishWithText(i18n("No contact found for \"%1\"", mSearchString));
        deleteLater();
        return;
    }
    QStringList entries;
    entries.reserve(contacts.count());
    for (const KContacts::Addressee &contact : contacts) {
        QString name = contact.realName();
        if (name.isEmpty()) {
            name = contact.organization();
        }
        if (name.isEmpty()) {
            name = contact.preferredEmail();
        }
        QStringList lines{name};
        if (mFields & ContactField::Email) {
            if (const QStringList emails = contact.emails(); !emails.isEmpty()) {
                lines.append(u"Email: "_s + emails.join(u", "_s));
            }
        }
        if (mFields & ContactField::Phone) {
            const KContacts::PhoneNumber::List phoneNumbers = contact.phoneNumbers();
            for (const KContacts::PhoneNumber &phoneNumber : phoneNumbers) {
                lines.append(u"Phone (%1): %2"_s.arg(phoneNumber.typeLabel(), phoneNumber.number()));
            }
        }
        if (mFields & ContactField::Location) {
            const KContacts::Address::List addresses = contact.addresses();
            for (const KContacts::Address &address : addresses) {
                lines.append(u"Location (%1): %2"_s.arg(address.typeLabel(), address.formatted(KContacts::AddressFormatStyle::SingleLineInternational)));
            }
        }
        if (mFields & ContactField::Birthday) {
            if (const QDateTime birthday = contact.birthday(); birthday.isValid()) {
                lines.append(u"Birthday: "_s + birthday.date().toString(Qt::ISODate));
            }
        }
        entries.append(lines.join(u"\n  "_s));
    }
    mToolCall->finishWithText(entries.join(u'\n'));
    deleteLater();
}
