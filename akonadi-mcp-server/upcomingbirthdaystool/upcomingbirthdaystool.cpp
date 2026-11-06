/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "upcomingbirthdaystool.h"
#include "common/toolutils.h"
#include "upcomingbirthdaystooljob.h"
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolArguments>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>

using namespace Qt::Literals::StringLiterals;
namespace
{
constexpr int defaultDays = 30;
constexpr int maximumDays = 366;
}
UpcomingBirthdaysTool::UpcomingBirthdaysTool() = default;
UpcomingBirthdaysTool::~UpcomingBirthdaysTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool UpcomingBirthdaysTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"contact_upcoming_birthdays"_s,
        i18n("Upcoming Birthdays"),
        u"List the contacts of the Akonadi address books whose birthday occurs in the coming days"_s,
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::ToolKind::ReadOnly,
        QMap<QString, QJsonObject>{
            {u"days"_s,
             TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::schemaProperty(u"integer"_s,
                                                                                        u"Number of days to look ahead, from 1 to 366 (default 30)"_s)}});
    ToolUtils::addToolMeta(tool, ToolUtils::Contact);
    return tool;
}

void UpcomingBirthdaysTool::doCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    int days = defaultDays;
    const QJsonValue daysValue = call->arguments().value(u"days"_s);
    if (const std::optional<qint64> daysInteger = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::integer(daysValue)) {
        if (*daysInteger < 1 || *daysInteger > maximumDays) {
            call->finishWithText(i18n("Argument days must be an integer between 1 and %1", maximumDays), true);
            return;
        }
        days = static_cast<int>(*daysInteger);
    } else if (TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments::isProvided(daysValue)) {
        call->finishWithText(i18n("Argument days must be an integer"), true);
        return;
    }

    auto job = new UpcomingBirthdaysToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setDays(days);
    job->start();
}
