/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "calendartooljobbase.h"
#include "akonadimcpprotocol_debug.h"
#include <Akonadi/CalendarUtils>
#include <Akonadi/ItemFetchScope>
#include <Akonadi/RecursiveItemFetchJob>
#include <KCalendarCore/MemoryCalendar>
#include <KJob>
#include <KLocalizedString>
#include <QTimeZone>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>

CalendarToolJobBase::CalendarToolJobBase(QObject *parent)
    : QObject{parent}
{
}

CalendarToolJobBase::~CalendarToolJobBase() = default;

bool CalendarToolJobBase::canStart() const
{
    return mToolCall;
}

void CalendarToolJobBase::start()
{
    if (!canStart()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << "CalendarToolJobBase can't start";
        if (mToolCall) {
            mToolCall->finishWithText(i18n("Invalid arguments"), true);
        }
        deleteLater();
        return;
    }

    mFetchJob = new Akonadi::RecursiveItemFetchJob(Akonadi::Collection::root(), mimeTypes(), this);
    mFetchJob->fetchScope().fetchFullPayload();
    connect(mFetchJob, &KJob::result, this, &CalendarToolJobBase::slotResult);
    connect(mToolCall, &TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall::cancelled, this, &CalendarToolJobBase::slotCancelled);
    mFetchJob->start();
}

void CalendarToolJobBase::slotCancelled()
{
    if (mFetchJob) {
        mFetchJob->kill();
    }
    deleteLater();
}

void CalendarToolJobBase::setMcpProtocolServerToolCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    mToolCall = call;
}

void CalendarToolJobBase::slotResult(KJob *job)
{
    if (!mToolCall) {
        deleteLater();
        return;
    }
    if (job->error()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << "Calendar fetch failed:" << job->errorString();
        mToolCall->finishWithText(i18n("Calendar fetch failed: %1", job->errorString()), true);
        deleteLater();
        return;
    }
    const auto calendar = KCalendarCore::MemoryCalendar::Ptr::create(QTimeZone::systemTimeZone());
    const Akonadi::Item::List items = qobject_cast<Akonadi::RecursiveItemFetchJob *>(job)->items();
    for (const Akonadi::Item &item : items) {
        if (const KCalendarCore::Incidence::Ptr incidence = Akonadi::CalendarUtils::incidence(item)) {
            calendar->addIncidence(incidence);
        }
    }
    mToolCall->finishWithText(generateResult(calendar));
    deleteLater();
}

#include "moc_calendartooljobbase.cpp"
