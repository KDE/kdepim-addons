/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "calendareventstool.h"
#include "calendarcommon/calendartoolutils.h"
#include "calendareventstooljob.h"
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;
namespace
{
constexpr int defaultDays = 7;
constexpr int maximumDays = 366;
}
CalendarEventsTool::CalendarEventsTool() = default;
CalendarEventsTool::~CalendarEventsTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool CalendarEventsTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"calendar_events"_s,
        u"List the events of the Akonadi calendars in a period, including the occurrences of recurring events"_s,
        QMap<QString, QJsonObject>{
            {u"start"_s,
             TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::schemaProperty(
                 u"string"_s,
                 u"Start of the period, as ISO 8601 date (2026-10-14) or local date-time (2026-10-14T14:00). Default: today"_s)},
            {u"end"_s,
             TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::schemaProperty(
                 u"string"_s,
                 u"End of the period, as ISO 8601 date or local date-time. A date includes the whole day. Default: 7 days after start, maximum 366 days"_s)}});

    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(true);
    annotation.setOpenWorldHint(false);
    tool.setTitle(i18n("Calendar Events"));
    tool.setAnnotations(annotation);
    return tool;
}

void CalendarEventsTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    QDateTime start = QDate::currentDate().startOfDay();
    if (const QJsonValue startValue = call->arguments().value(u"start"_s); !startValue.isUndefined() && !startValue.isNull()) {
        const std::optional<QDateTime> dateTime = CalendarToolUtils::parseDateTime(startValue.toString(), CalendarToolUtils::DateBound::Start);
        if (!dateTime) {
            call->finishWithText(i18n("Argument start must be an ISO 8601 date or date-time"), true);
            return;
        }
        start = *dateTime;
    }
    QDateTime end = start.addDays(defaultDays);
    if (const QJsonValue endValue = call->arguments().value(u"end"_s); !endValue.isUndefined() && !endValue.isNull()) {
        const std::optional<QDateTime> dateTime = CalendarToolUtils::parseDateTime(endValue.toString(), CalendarToolUtils::DateBound::End);
        if (!dateTime) {
            call->finishWithText(i18n("Argument end must be an ISO 8601 date or date-time"), true);
            return;
        }
        end = *dateTime;
    }
    if (end <= start) {
        call->finishWithText(i18n("Argument end must be after start"), true);
        return;
    }
    if (start.daysTo(end) > maximumDays) {
        call->finishWithText(i18n("Period must not exceed %1 days", maximumDays), true);
        return;
    }

    auto job = new CalendarEventsToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setStart(start);
    job->setEnd(end);
    job->start();
}
