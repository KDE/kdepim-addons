/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "upcomingbirthdaystooljob.h"
#include "akonadimcpprotocol_debug.h"
#include <Akonadi/ItemFetchScope>
#include <Akonadi/RecursiveItemFetchJob>
#include <KContacts/Addressee>
#include <KJob>
#include <KLocalizedString>
#include <QDate>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <algorithm>

using namespace Qt::Literals::StringLiterals;

namespace
{
struct UpcomingBirthday {
    QDate date;
    QString entry;
};

[[nodiscard]] QDate birthdayInYear(QDate birthday, int year)
{
    QDate date(year, birthday.month(), birthday.day());
    if (!date.isValid()) {
        // February 29 on a non-leap year
        date = QDate(year, 2, 28);
    }
    return date;
}
}

UpcomingBirthdaysToolJob::UpcomingBirthdaysToolJob(QObject *parent)
    : QObject{parent}
{
}

UpcomingBirthdaysToolJob::~UpcomingBirthdaysToolJob() = default;

void UpcomingBirthdaysToolJob::setDays(int days)
{
    mDays = days;
}

bool UpcomingBirthdaysToolJob::canStart() const
{
    return mDays > 0 && mToolCall;
}

void UpcomingBirthdaysToolJob::start()
{
    if (!canStart()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << "UpcomingBirthdaysToolJob can't start";
        if (mToolCall) {
            mToolCall->finishWithText(i18n("Number of days must be a positive integer"), true);
        }
        deleteLater();
        return;
    }

    mFetchJob = new Akonadi::RecursiveItemFetchJob(Akonadi::Collection::root(), {KContacts::Addressee::mimeType()}, this);
    mFetchJob->fetchScope().fetchFullPayload();
    connect(mFetchJob, &KJob::result, this, &UpcomingBirthdaysToolJob::slotResult);
    connect(mToolCall, &TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall::cancelled, this, &UpcomingBirthdaysToolJob::slotCancelled);
    mFetchJob->start();
}

void UpcomingBirthdaysToolJob::slotCancelled()
{
    if (mFetchJob) {
        mFetchJob->kill();
    }
    deleteLater();
}

void UpcomingBirthdaysToolJob::setMcpProtocolServerToolCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    mToolCall = call;
}

void UpcomingBirthdaysToolJob::slotResult(KJob *job)
{
    if (!mToolCall) {
        deleteLater();
        return;
    }
    if (job->error()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << "Contact fetch failed:" << job->errorString();
        mToolCall->finishWithText(i18n("Contact fetch failed: %1", job->errorString()), true);
        deleteLater();
        return;
    }
    const QDate today = QDate::currentDate();
    const QDate lastDay = today.addDays(mDays);
    const Akonadi::Item::List items = qobject_cast<Akonadi::RecursiveItemFetchJob *>(job)->items();
    QList<UpcomingBirthday> birthdays;
    for (const Akonadi::Item &item : items) {
        if (!item.hasPayload<KContacts::Addressee>()) {
            continue;
        }
        const auto contact = item.payload<KContacts::Addressee>();
        const QDate birthday = contact.birthday().date();
        if (!birthday.isValid()) {
            continue;
        }
        QDate nextBirthday = birthdayInYear(birthday, today.year());
        if (nextBirthday < today) {
            nextBirthday = birthdayInYear(birthday, today.year() + 1);
        }
        if (nextBirthday > lastDay) {
            continue;
        }
        QString name = contact.realName();
        if (name.isEmpty()) {
            name = contact.preferredEmail();
        }
        const int age = nextBirthday.year() - birthday.year();
        birthdays.append({nextBirthday, u"%1: %2 (turns %3)"_s.arg(nextBirthday.toString(Qt::ISODate), name, QString::number(age))});
    }
    if (birthdays.isEmpty()) {
        mToolCall->finishWithText(i18np("No birthday in the next day", "No birthday in the next %1 days", mDays));
        deleteLater();
        return;
    }
    std::ranges::sort(birthdays, {}, &UpcomingBirthday::date);
    QStringList entries;
    entries.reserve(birthdays.count());
    for (const UpcomingBirthday &birthday : std::as_const(birthdays)) {
        entries.append(birthday.entry);
    }
    mToolCall->finishWithText(entries.join(u'\n'));
    deleteLater();
}
