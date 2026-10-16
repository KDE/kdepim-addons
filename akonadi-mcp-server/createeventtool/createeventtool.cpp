/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "createeventtool.h"
#include "calendarcommon/calendartoolutils.h"
#include "calendarcommon/createincidencetooljob.h"
#include <KCalendarCore/Event>
#include <KLocalizedString>
#include <QJsonValue>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;
namespace
{
constexpr int defaultDurationSecs = 3600;
}
CreateEventTool::CreateEventTool() = default;
CreateEventTool::~CreateEventTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool CreateEventTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"create_event"_s,
        u"Create a new event in an Akonadi calendar"_s,
        QMap<QString, QJsonObject>{
            {u"summary"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Title of the event"_s)},
            {u"start"_s,
             McpProtocolServerTool::schemaProperty(
                 u"string"_s,
                 u"Start of the event, as ISO 8601 date (2026-10-14) for an all-day event or local date-time (2026-10-14T14:00)"_s)},
            {u"end"_s,
             McpProtocolServerTool::schemaProperty(
                 u"string"_s,
                 u"End of the event, same format as start. For an all-day event, the date is the last day of the event. Default: one hour after start, or the same day for an all-day event"_s)},
            {u"location"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Location of the event"_s)},
            {u"description"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Description of the event"_s)},
            {u"calendar_id"_s,
             McpProtocolServerTool::schemaProperty(u"integer"_s,
                                                   u"Identifier of the calendar (see list_calendars). If omitted, the first writable calendar is used"_s)}},
        {u"summary"_s, u"start"_s});
    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(false);
    annotation.setDestructiveHint(false);
    annotation.setIdempotentHint(false);
    annotation.setOpenWorldHint(false);
    annotation.setTitle(i18n("Create Event"));
    tool.setAnnotations(annotation);
    return tool;
}

void CreateEventTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const auto arguments = call->arguments();
    const QString summary = arguments.value(u"summary"_s).toString().trimmed();
    if (summary.isEmpty()) {
        call->finishWithText(i18n("Argument summary must be a non-empty string"), true);
        return;
    }

    const std::optional<CalendarToolUtils::IncidenceDateTime> start = CalendarToolUtils::parseIncidenceDateTime(arguments.value(u"start"_s).toString());
    if (!start) {
        call->finishWithText(i18n("Argument start must be an ISO 8601 date or date-time"), true);
        return;
    }

    QDateTime end = start->allDay ? start->dateTime : start->dateTime.addSecs(defaultDurationSecs);
    if (const QJsonValue endValue = arguments.value(u"end"_s); !endValue.isUndefined() && !endValue.isNull()) {
        const std::optional<CalendarToolUtils::IncidenceDateTime> endDateTime = CalendarToolUtils::parseIncidenceDateTime(endValue.toString());
        if (!endDateTime) {
            call->finishWithText(i18n("Argument end must be an ISO 8601 date or date-time"), true);
            return;
        }
        if (endDateTime->allDay != start->allDay) {
            call->finishWithText(i18n("Arguments start and end must both be dates or both be date-times"), true);
            return;
        }
        end = endDateTime->dateTime;
    }
    if (end < start->dateTime) {
        call->finishWithText(i18n("Argument end must not be before start"), true);
        return;
    }

    const auto event = KCalendarCore::Event::Ptr::create();
    event->setSummary(summary);
    event->setDtStart(start->dateTime);
    event->setDtEnd(end);
    event->setAllDay(start->allDay);
    if (const QString location = arguments.value(u"location"_s).toString().trimmed(); !location.isEmpty()) {
        event->setLocation(location);
    }
    if (const QString description = arguments.value(u"description"_s).toString().trimmed(); !description.isEmpty()) {
        event->setDescription(description);
    }

    Akonadi::Collection::Id calendarId = -1;
    const QJsonValue calendarValue = arguments.value(u"calendar_id"_s);
    if (calendarValue.isDouble()) {
        calendarId = calendarValue.toInteger(-1);
        if (calendarId < 0) {
            call->finishWithText(i18n("Argument calendar_id must be a positive integer"), true);
            return;
        }
    } else if (!calendarValue.isUndefined() && !calendarValue.isNull()) {
        call->finishWithText(i18n("Argument calendar_id must be an integer"), true);
        return;
    }

    auto job = new CreateIncidenceToolJob(call);
    job->setMcpProtocolServerToolCall(call);
    job->setIncidence(event);
    job->setCalendarId(calendarId);
    job->start();
}
