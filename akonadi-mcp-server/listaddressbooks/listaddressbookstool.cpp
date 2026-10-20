/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "listaddressbookstool.h"
#include "common/toolutils.h"
#include "listaddressbookstooljob.h"
#include <KLocalizedString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;
ListAddressBooksTool::ListAddressBooksTool() = default;
ListAddressBooksTool::~ListAddressBooksTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool ListAddressBooksTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool =
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(u"contact_list_address_books"_s, u"List the Akonadi address books"_s);

    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(true);
    annotation.setOpenWorldHint(false);
    tool.setTitle(i18n("List Address Books"));
    tool.setAnnotations(annotation);
    ToolUtils::addToolMeta(tool, ToolUtils::Contact);
    return tool;
}

void ListAddressBooksTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    auto job = new ListAddressBooksToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->start();
}
