/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "createcontactgrouptool.h"
#include "common/toolutils.h"
#include "createcontactgrouptooljob.h"
#include <KLocalizedString>
#include <QJsonArray>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;

namespace
{
// An undefined or null value is accepted, returns false if value is not an array of positive integers
[[nodiscard]] bool readIdList(const QJsonValue &value, QList<Akonadi::Item::Id> &ids)
{
    if (!ToolUtils::isProvided(value)) {
        return true;
    }
    if (!value.isArray()) {
        return false;
    }
    const QJsonArray array = value.toArray();
    for (const QJsonValue &element : array) {
        if (!element.isDouble() || element.toInteger(-1) < 0) {
            return false;
        }
        ids.append(element.toInteger());
    }
    return true;
}
}

CreateContactGroupTool::CreateContactGroupTool() = default;
CreateContactGroupTool::~CreateContactGroupTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool CreateContactGroupTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"contact_group_create"_s,
        u"Create a new contact group (distribution list) in an Akonadi address book"_s,
        QMap<QString, QJsonObject>{
            {u"name"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Name of the contact group"_s)},
            {u"contact_ids"_s,
             McpProtocolServerTool::schemaArrayProperty(McpProtocolServerTool::schemaProperty(u"integer"_s, {}),
                                                        u"Identifiers of existing contacts to add to the group (see contact_search)"_s)},
            {u"emails"_s,
             McpProtocolServerTool::schemaArrayProperty(McpProtocolServerTool::schemaProperty(u"string"_s, {}),
                                                        u"Email addresses of members which are not in an address book, as \"Name <email>\" or a bare email"_s)},
            {u"address_book_id"_s,
             McpProtocolServerTool::schemaProperty(
                 u"integer"_s,
                 u"Identifier of the address book (see contact_list_address_books). If omitted, the first writable address book is used"_s)}},
        {u"name"_s});
    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(false);
    annotation.setDestructiveHint(false);
    annotation.setIdempotentHint(false);
    annotation.setOpenWorldHint(false);
    tool.setTitle(i18n("Create Contact Group"));
    tool.setAnnotations(annotation);
    ToolUtils::addToolMeta(tool, ToolUtils::Contact);
    return tool;
}

void CreateContactGroupTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const auto arguments = call->arguments();
    const QString name = arguments.value(u"name"_s).toString().trimmed();
    if (name.isEmpty()) {
        call->finishWithText(i18n("Argument name must be a non-empty string"), true);
        return;
    }

    QList<Akonadi::Item::Id> contactIds;
    if (!readIdList(arguments.value(u"contact_ids"_s), contactIds)) {
        call->finishWithText(i18n("Argument contact_ids must be an array of positive integers"), true);
        return;
    }

    QStringList emails;
    if (!ToolUtils::readStringList(arguments.value(u"emails"_s), emails)) {
        call->finishWithText(i18n("Argument emails must be an array of strings"), true);
        return;
    }

    Akonadi::Collection::Id addressBookId = -1;
    if (const QJsonValue addressBookValue = arguments.value(u"address_book_id"_s); ToolUtils::isProvided(addressBookValue)) {
        if (!addressBookValue.isDouble() || addressBookValue.toInteger(-1) < 0) {
            call->finishWithText(i18n("Argument address_book_id must be a positive integer"), true);
            return;
        }
        addressBookId = addressBookValue.toInteger();
    }

    auto job = new CreateContactGroupToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setName(name);
    job->setContactIds(contactIds);
    job->setEmails(emails);
    job->setAddressBookId(addressBookId);
    job->start();
}
