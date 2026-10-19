/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "createjournaltool.h"
#include "calendarcommon/calendartoolutils.h"
#include "calendarcommon/createincidencetooljob.h"
#include <KCalendarCore/Journal>
#include <KLocalizedString>
#include <QJsonValue>
#include <QTimeZone>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolAnnotations>

using namespace Qt::Literals::StringLiterals;

CreateJournalTool::CreateJournalTool() = default;
CreateJournalTool::~CreateJournalTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool CreateJournalTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool = TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(
        u"calendar_create_journal"_s,
        u"Create a new journal entry in an Akonadi calendar"_s,
        QMap<QString, QJsonObject>{
            {u"summary"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Title of the journal entry"_s)},
            {u"date"_s,
             McpProtocolServerTool::schemaProperty(
                 u"string"_s,
                 u"Date of the entry, as ISO 8601 date (2026-10-14) or local date-time (2026-10-14T14:00). Default: today"_s)},
            {u"description"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Text of the journal entry"_s)},
            {u"calendar_id"_s,
             McpProtocolServerTool::schemaProperty(u"integer"_s,
                                                   u"Identifier of the calendar (see calendar_list). If omitted, the first writable calendar is used"_s)}},
        {u"summary"_s});
    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(false);
    annotation.setDestructiveHint(false);
    annotation.setIdempotentHint(false);
    annotation.setOpenWorldHint(false);
    tool.setTitle(i18n("Create Journal Entry"));
    tool.setAnnotations(annotation);
    return tool;
}

void CreateJournalTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const auto arguments = call->arguments();
    const QString summary = arguments.value(u"summary"_s).toString().trimmed();
    if (summary.isEmpty()) {
        call->finishWithText(i18n("Argument summary must be a non-empty string"), true);
        return;
    }

    CalendarToolUtils::IncidenceDateTime date{QDate::currentDate().startOfDay(QTimeZone::systemTimeZone()), true};
    if (const QJsonValue dateValue = arguments.value(u"date"_s); !dateValue.isUndefined() && !dateValue.isNull()) {
        const std::optional<CalendarToolUtils::IncidenceDateTime> dateTime = CalendarToolUtils::parseIncidenceDateTime(dateValue.toString());
        if (!dateTime) {
            call->finishWithText(i18n("Argument date must be an ISO 8601 date or date-time"), true);
            return;
        }
        date = *dateTime;
    }

    const auto journal = KCalendarCore::Journal::Ptr::create();
    journal->setSummary(summary);
    journal->setDtStart(date.dateTime);
    journal->setAllDay(date.allDay);
    if (const QString description = arguments.value(u"description"_s).toString().trimmed(); !description.isEmpty()) {
        journal->setDescription(description);
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
    job->setIncidence(journal);
    job->setCalendarId(calendarId);
    job->start();
}
