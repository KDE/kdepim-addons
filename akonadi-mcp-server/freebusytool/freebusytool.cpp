/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "freebusytool.h"
#include "calendarcommon/calendartoolutils.h"
#include "freebusytooljob.h"
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;
namespace
{
constexpr int maximumDays = 31;
}
FreeBusyTool::FreeBusyTool() = default;
FreeBusyTool::~FreeBusyTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool FreeBusyTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"calendar_free_busy"_s,
        u"Return the busy and free periods of the user in the Akonadi calendars, to know if a time slot is available"_s,
        QMap<QString, QJsonObject>{
            {u"start"_s,
             TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::schemaProperty(
                 u"string"_s,
                 u"Start of the period, as ISO 8601 date (2026-10-14) or local date-time (2026-10-14T14:00)"_s)},
            {u"end"_s,
             TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::schemaProperty(
                 u"string"_s,
                 u"End of the period, as ISO 8601 date or local date-time. A date includes the whole day. Maximum 31 days after start"_s)}},
        {u"start"_s, u"end"_s});

    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(true);
    annotation.setOpenWorldHint(false);
    tool.setTitle(i18n("Free/Busy"));
    tool.setAnnotations(annotation);
    return tool;
}

void FreeBusyTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const std::optional<QDateTime> start =
        CalendarToolUtils::parseDateTime(call->arguments().value(u"start"_s).toString(), CalendarToolUtils::DateBound::Start);
    if (!start) {
        call->finishWithText(i18n("Argument start must be an ISO 8601 date or date-time"), true);
        return;
    }
    const std::optional<QDateTime> end = CalendarToolUtils::parseDateTime(call->arguments().value(u"end"_s).toString(), CalendarToolUtils::DateBound::End);
    if (!end) {
        call->finishWithText(i18n("Argument end must be an ISO 8601 date or date-time"), true);
        return;
    }
    if (*end <= *start) {
        call->finishWithText(i18n("Argument end must be after start"), true);
        return;
    }
    if (start->daysTo(*end) > maximumDays) {
        call->finishWithText(i18n("Period must not exceed %1 days", maximumDays), true);
        return;
    }

    auto job = new FreeBusyToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setStart(*start);
    job->setEnd(*end);
    job->start();
}
