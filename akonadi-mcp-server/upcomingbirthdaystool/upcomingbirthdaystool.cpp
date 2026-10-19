/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "upcomingbirthdaystool.h"
#include "upcomingbirthdaystooljob.h"
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

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
        u"List the contacts of the Akonadi address books whose birthday occurs in the coming days"_s,
        QMap<QString, QJsonObject>{
            {u"days"_s,
             TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::schemaProperty(u"integer"_s,
                                                                                        u"Number of days to look ahead, from 1 to 366 (default 30)"_s)}});

    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(true);
    annotation.setOpenWorldHint(false);
    tool.setTitle(i18n("Upcoming Birthdays"));
    tool.setAnnotations(annotation);
    return tool;
}

void UpcomingBirthdaysTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    int days = defaultDays;
    const QJsonValue daysValue = call->arguments().value(u"days"_s);
    if (daysValue.isDouble()) {
        days = daysValue.toInt(-1);
        if (days < 1 || days > maximumDays) {
            call->finishWithText(i18n("Argument days must be an integer between 1 and %1", maximumDays), true);
            return;
        }
    } else if (!daysValue.isUndefined() && !daysValue.isNull()) {
        call->finishWithText(i18n("Argument days must be an integer"), true);
        return;
    }

    auto job = new UpcomingBirthdaysToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setDays(days);
    job->start();
}
