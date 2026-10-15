/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "createcontacttool.h"
#include "createcontacttooljob.h"
#include <KContacts/Addressee>
#include <KLocalizedString>
#include <QDate>
#include <QJsonArray>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;
namespace
{
bool readStringList(const QJsonValue &value, QStringList &list)
{
    if (value.isUndefined() || value.isNull()) {
        return true;
    }
    if (!value.isArray()) {
        return false;
    }
    const QJsonArray array = value.toArray();
    for (const QJsonValue &element : array) {
        if (!element.isString()) {
            return false;
        }
        if (const QString str = element.toString().trimmed(); !str.isEmpty()) {
            list.append(str);
        }
    }
    return true;
}
}

CreateContactTool::CreateContactTool() = default;
CreateContactTool::~CreateContactTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool CreateContactTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"create_contact"_s,
        u"Create a new contact in an Akonadi address book"_s,
        QMap<QString, QJsonObject>{
            {u"name"_s, TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::schemaProperty(u"string"_s, u"Full name of the contact"_s)},
            {u"emails"_s,
             McpProtocolServerTool::schemaArrayProperty(McpProtocolServerTool::schemaProperty(u"string"_s, {}),
                                                        u"Email addresses, the first one is the preferred one"_s)},
            {u"phone_numbers"_s, McpProtocolServerTool::schemaArrayProperty(McpProtocolServerTool::schemaProperty(u"string"_s, {}), u"Phone numbers"_s)},
            {u"organization"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Organization of the contact"_s)},
            {u"birthday"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Birthday in ISO format (YYYY-MM-DD)"_s)},
            {u"note"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Free text note"_s)},
            {u"address_book_id"_s,
             McpProtocolServerTool::schemaProperty(
                 u"integer"_s,
                 u"Identifier of the address book (see list_address_books). If omitted, the first writable address book is used"_s)}},
        {u"name"_s});
    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(false);
    annotation.setDestructiveHint(false);
    annotation.setIdempotentHint(false);
    annotation.setOpenWorldHint(false);
    annotation.setTitle(i18n("Create Contact"));
    tool.setAnnotations(annotation);
    return tool;
}

void CreateContactTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const auto arguments = call->arguments();
    const QString name = arguments.value(u"name"_s).toString().trimmed();
    if (name.isEmpty()) {
        call->finishWithText(i18n("Argument name must be a non-empty string"), true);
        return;
    }

    KContacts::Addressee contact;
    contact.setNameFromString(name);
    contact.setFormattedName(name);

    QStringList emails;
    if (!readStringList(arguments.value(u"emails"_s), emails)) {
        call->finishWithText(i18n("Argument emails must be an array of strings"), true);
        return;
    }
    contact.setEmails(emails);

    QStringList phoneNumbers;
    if (!readStringList(arguments.value(u"phone_numbers"_s), phoneNumbers)) {
        call->finishWithText(i18n("Argument phone_numbers must be an array of strings"), true);
        return;
    }
    for (const QString &phoneNumber : std::as_const(phoneNumbers)) {
        contact.insertPhoneNumber(KContacts::PhoneNumber(phoneNumber));
    }

    if (const QString organization = arguments.value(u"organization"_s).toString().trimmed(); !organization.isEmpty()) {
        contact.setOrganization(organization);
    }
    if (const QString note = arguments.value(u"note"_s).toString().trimmed(); !note.isEmpty()) {
        contact.setNote(note);
    }
    if (const QString birthdayStr = arguments.value(u"birthday"_s).toString().trimmed(); !birthdayStr.isEmpty()) {
        const QDate birthday = QDate::fromString(birthdayStr, Qt::ISODate);
        if (!birthday.isValid()) {
            call->finishWithText(i18n("Invalid birthday \"%1\", expected format is YYYY-MM-DD", birthdayStr), true);
            return;
        }
        contact.setBirthday(birthday);
    }

    Akonadi::Collection::Id addressBookId = -1;
    const QJsonValue addressBookValue = arguments.value(u"address_book_id"_s);
    if (addressBookValue.isDouble()) {
        addressBookId = addressBookValue.toInteger(-1);
        if (addressBookId < 0) {
            call->finishWithText(i18n("Argument address_book_id must be a positive integer"), true);
            return;
        }
    } else if (!addressBookValue.isUndefined() && !addressBookValue.isNull()) {
        call->finishWithText(i18n("Argument address_book_id must be an integer"), true);
        return;
    }

    auto job = new CreateContactToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setContact(contact);
    job->setAddressBookId(addressBookId);
    job->start();
}
