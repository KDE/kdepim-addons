/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "kaichatcalendarpluginjob.h"
#include "kaichat_calendarplugin_debug.h"
#include "kaichatcalendarpluginutils.h"
#include <Akonadi/ContactSearchJob>
#include <KJob>
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
KAIChatCalendarPluginJob::KAIChatCalendarPluginJob(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextToolPluginJob{parent}
{
}

KAIChatCalendarPluginJob::~KAIChatCalendarPluginJob() = default;

void KAIChatCalendarPluginJob::start()
{
    if (!canStart()) {
        qCWarning(KAICHAT_CALENDAR_LOG) << " Impossible to start KAIChatCalendarPluginJob" << *this;
        deleteLater();
        return;
    }

    qDebug() << " toolArguments " << toolArguments();
    Q_EMIT toolInProgress(i18n("Get Email..."));
    QString userName;
    const QStringList lst = requiredArguments();
    KAIChatCalendarPluginUtils::CalendarEnum typecalendar = KAIChatCalendarPluginUtils::CalendarEnum::Unknown;
    for (const auto &arg : lst) {
        for (const auto &resultTool : std::as_const(mToolArguments)) {
            if (resultTool.keyTool == arg) {
                const QString value = resultTool.value;
                if (arg == "calendarinfo"_L1) {
                    typecalendar = KAIChatCalendarPluginUtils::convertStringToCalendarEnum(value);
                } else if (arg == "username"_L1) {
                    userName = value;
                } else {
                    qCWarning(KAICHAT_CALENDAR_LOG) << "Invalid argument : " << value;
                }
            }
        }
    }
    switch (typecalendar) {
    case KAIChatCalendarPluginUtils::CalendarEnum::Email: {
        auto job = new Akonadi::ContactSearchJob(this);
        job->setProperty("userName", userName.toUtf8());
        job->setQuery(Akonadi::ContactSearchJob::Email, userName, Akonadi::ContactSearchJob::ExactMatch);
        connect(job, &KJob::result, this, &KAIChatCalendarPluginJob::slotContactEmailSearchDone);
        break;
    }
    case KAIChatCalendarPluginUtils::CalendarEnum::Unknown:
        qCWarning(KAICHAT_CALENDAR_LOG) << "Invalid calendar argument";
        deleteLater();
        break;
    }
}

void KAIChatCalendarPluginJob::slotContactBirthdaySearchDone(KJob *job)
{
    const Akonadi::ContactSearchJob *searchJob = qobject_cast<Akonadi::ContactSearchJob *>(job);
    if (searchJob->contacts().isEmpty()) {
        Q_EMIT finished(i18n("No Contact found in calendar for %1", job->property("userName").toString()), mMessageUuid, mChatId, mToolIdentifier);
    } else {
        const KContacts::Addressee contact = searchJob->contacts().constFirst();
        qDebug() << " contact " << contact.toString();
        const QString result = i18n("Birthday for %1 is %2", job->property("userName").toString(), contact.birthday().toString());
        Q_EMIT finished(result, mMessageUuid, mChatId, mToolIdentifier);
    }
    deleteLater();
}

void KAIChatCalendarPluginJob::slotContactEmailSearchDone(KJob *job)
{
    const Akonadi::ContactSearchJob *searchJob = qobject_cast<Akonadi::ContactSearchJob *>(job);
    if (searchJob->contacts().isEmpty()) {
        Q_EMIT finished(i18n("No Contact found in calendar for %1", job->property("userName").toString()), mMessageUuid, mChatId, mToolIdentifier);
    } else {
        const KContacts::Addressee contact = searchJob->contacts().constFirst();
        qDebug() << " contact " << contact.toString();
        const QString result = i18n("The preferred email is %1", contact.preferredEmail());
        Q_EMIT finished(result, mMessageUuid, mChatId, mToolIdentifier);
    }
    deleteLater();
}

#include "moc_kaichatcalendarpluginjob.cpp"
