/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "contactsearchtooljob.h"
#include <Akonadi/ContactSearchJob>
#include <KJob>
#include <KLocalizedString>
#include <QDateTime>

using namespace Qt::Literals::StringLiterals;

ContactSearchToolJob::ContactSearchToolJob(QObject *parent)
    : ToolJobBase{parent}
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
    return ToolJobBase::canStart() && !mSearchString.isEmpty();
}

QString ContactSearchToolJob::invalidArgumentsMessage() const
{
    return i18n("Search string must be a non-empty string");
}

void ContactSearchToolJob::startJob()
{
    auto searchJob = new Akonadi::ContactSearchJob(this);
    searchJob->setQuery(Akonadi::ContactSearchJob::NameOrEmail, mSearchString, Akonadi::ContactSearchJob::ContainsMatch);
    connect(searchJob, &KJob::result, this, &ContactSearchToolJob::slotResult);
    setCurrentJob(searchJob);
}

void ContactSearchToolJob::slotResult(KJob *job)
{
    if (!checkJobResult(job, ki18n("Contact search failed: %1"))) {
        return;
    }
    const KContacts::Addressee::List contacts = qobject_cast<Akonadi::ContactSearchJob *>(job)->contacts();
    if (contacts.isEmpty()) {
        finish(i18n("No contact found for \"%1\"", mSearchString));
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
    finish(entries.join(u'\n'));
}

#include "moc_contactsearchtooljob.cpp"
