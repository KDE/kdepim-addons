/*
  SPDX-FileCopyrightText: 2001 Cornelius Schumacher <schumacher@kde.org>
  SPDX-FileCopyrightText: 2004 Reinhold Kainhofer <reinhold@kainhofer.com>
  SPDX-FileCopyrightText: 2005 Rafal Rzepecki <divide@users.sourceforge.net>
  SPDX-FileCopyrightText: 2009-2010 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "itipformatter.h"

#include <MessageViewer/MessagePartRendererManager>

#include <GrantleeTheme/GrantleeKi18nLocalizer>
#include <GrantleeTheme/GrantleeThemeEngine>

#include <KCalendarCore/Event>
#include <KCalendarCore/Exceptions>
#include <KCalendarCore/FreeBusy>
#include <KCalendarCore/ICalFormat>
#include <KCalendarCore/Journal>
#include <KCalendarCore/Todo>
#include <KCalendarCore/Visitor>

#if KCALENDARCORE_VERSION < QT_VERSION_CHECK(6, 30, 0)
#include <KCalUtils/IncidenceFormatter>
#include <KCalUtils/Stringify>
#endif

#include <KIdentityManagementCore/Utils>

#include <KEmailAddress>
#include <KFormat>
#include <KLocalizedString>
#include <ktexttemplate_version.h>
#include <ktexttohtml.h>

#include <QApplication>
#include <QLocale>
#include <QMimeDatabase>
#include <QPalette>
#include <QTextDocumentFragment>

using namespace Qt::Literals;
using namespace KCalendarCore;

/*******************
 *  General helpers
 *******************/

static QString dateTimeToString(const QDateTime &date, bool allDay, bool shortfmt);

/*!
  Format the start and end dates/times of an incidence.
  \param start the start date/time
  \param end the end date/time
  \param isAllDay if true, the incidence is all-day; otherwise time information is included
  \return the formatted start and end string
*/
static QString formatStartEnd(const QDateTime &start, const QDateTime &end, bool isAllDay);

static QVariantHash inviteButton(const QString &id, const QString &text, const QString &iconName, InvitationFormatterHelper *helper);

//@cond PRIVATE
static QString cleanHtml(const QString &html)
{
    return QTextDocumentFragment::fromHtml(html).toPlainText();
}

[[nodiscard]] static QString string2HTML(const QString &str)
{
    // use convertToHtml so we get clickable links and other goodies
    return KTextToHTML::convertToHtml(str, KTextToHTML::HighlightText | KTextToHTML::ReplaceSmileys);
}

[[nodiscard]] static bool thatIsMe(const QString &email)
{
    return KIdentityManagementCore::thatIsMe(email);
}

[[nodiscard]] static bool iamAttendee(const Attendee &attendee)
{
    // Check if this attendee is the user
    return thatIsMe(attendee.email());
}

static QString htmlAddTag(QStringView tag, QString text)
{
    return '<'_L1 + tag + '>'_L1 + std::move(text).replace("\n"_L1, "<br>"_L1) + "</"_L1 + tag + '>'_L1;
}

[[nodiscard]] static bool iamOrganizer(const Incidence::Ptr &incidence)
{
    // Check if the user is the organizer for this incidence

    if (!incidence) {
        return false;
    }

    return thatIsMe(incidence->organizer().email());
}

[[nodiscard]] static bool senderIsOrganizer(const Incidence::Ptr &incidence, const QString &sender)
{
    // Check if the specified sender is the organizer

    if (!incidence || sender.isEmpty()) {
        return true;
    }

    bool isorg = true;
    QString senderName;
    QString senderEmail;
    if (KEmailAddress::extractEmailAddressAndName(sender, senderEmail, senderName)) {
        // for this heuristic, we say the sender is the organizer if either the name or the email match.
        if (incidence->organizer().email() != senderEmail && incidence->organizer().name() != senderName) {
            isorg = false;
        }
    }
    return isorg;
}

[[nodiscard]] static bool attendeeIsOrganizer(const Incidence::Ptr &incidence, const Attendee &attendee)
{
    if (incidence && !attendee.isNull() && (incidence->organizer().email() == attendee.email())) {
        return true;
    } else {
        return false;
    }
}

[[nodiscard]] static QString organizerName(const Incidence::Ptr &incidence, const QString &defName)
{
    QString tName;
    if (!defName.isEmpty()) {
        tName = defName;
    } else {
        tName = i18n("Organizer Unknown");
    }

    QString name;
    if (incidence) {
        name = incidence->organizer().name();
        if (name.isEmpty()) {
            name = incidence->organizer().email();
        }
    }
    if (name.isEmpty()) {
        name = tName;
    }
    return name;
}

[[nodiscard]] static QString firstAttendeeName(const Incidence::Ptr &incidence, const QString &defName)
{
    QString tName;
    if (!defName.isEmpty()) {
        tName = defName;
    } else {
        tName = i18n("Sender");
    }

    QString name;
    if (incidence) {
        const Attendee::List attendees = incidence->attendees();
        if (!attendees.isEmpty()) {
            const Attendee &attendee = attendees.at(0);
            name = attendee.name();
            if (name.isEmpty()) {
                name = attendee.email();
            }
        }
    }
    if (name.isEmpty()) {
        name = tName;
    }
    return name;
}

[[nodiscard]] static QString rsvpStatusIconName(Attendee::PartStat status)
{
    switch (status) {
    case Attendee::Accepted:
        return QStringLiteral("dialog-ok-apply");
    case Attendee::Declined:
        return QStringLiteral("dialog-cancel");
    case Attendee::NeedsAction: // NOLINT(bugprone-branch-clone)
        return QStringLiteral("help-about");
    case Attendee::InProcess:
        return QStringLiteral("help-about");
    case Attendee::Tentative:
        return QStringLiteral("dialog-ok");
    case Attendee::Delegated:
        return QStringLiteral("mail-forward");
    case Attendee::Completed:
        return QStringLiteral("mail-mark-read");
    default:
        return QString();
    }
}

//@endcond

/***********************************************************************
 *  Helper functions for the body part formatter of kmail (Invitations)
 ***********************************************************************/

//@cond PRIVATE
static QString invitationSummary(const Incidence::Ptr &incidence)
{
    if (!incidence->summary().isEmpty()) {
        if (!incidence->summaryIsRich()) {
            return incidence->summary().toHtmlEscaped();
        } else {
            return cleanHtml(incidence->richSummary());
        }
    }
    return i18n("Summary unspecified");
}

static QString invitationLocation(const Incidence::Ptr &incidence)
{
    if (!incidence->location().isEmpty()) {
        if (!incidence->locationIsRich()) {
            return incidence->location().toHtmlEscaped();
        } else {
            return cleanHtml(incidence->richLocation());
        }
    }
    return i18n("Location unspecified");
}

[[nodiscard]] static QString diffColor()
{
    // Color for printing comparison differences inside invitations.

    //  return  "#DE8519"; // hard-coded color from Outlook2007
    return QColor(Qt::red).name(); // krazy:exclude=qenums TODO make configurable
}

[[nodiscard]] static QString noteColor()
{
    // Color for printing notes inside invitations.
    return qApp->palette().color(QPalette::Active, QPalette::Highlight).name();
}

[[nodiscard]] static QString htmlCompare(QString value, const QString &oldvalue)
{
    // if 'value' is empty, then print nothing
    if (value.isEmpty()) {
        return QString();
    }

    // if 'value' is new or unchanged, then print normally
    if (oldvalue.isEmpty() || value == oldvalue) {
        return value;
    }

    // if 'value' has changed, then make a special print
    return QStringLiteral("<font color=\"%1\">%2</font> (<strike>%3</strike>)").arg(diffColor(), value, oldvalue);
}

[[nodiscard]] static Attendee findDelegatedFromMyAttendee(const Incidence::Ptr &incidence)
{
    // Return the first attendee that was delegated-from the user

    Attendee attendee;
    if (!incidence) {
        return attendee;
    }

    QString delegatorName;
    QString delegatorEmail;
    const Attendee::List attendees = incidence->attendees();
    for (const auto &a : attendees) {
        KEmailAddress::extractEmailAddressAndName(a.delegator(), delegatorEmail, delegatorName);
        if (thatIsMe(delegatorEmail)) {
            attendee = a;
            break;
        }
    }

    return attendee;
}

[[nodiscard]] static Attendee findMyAttendee(const Incidence::Ptr &incidence)
{
    // Return the attendee for the incidence that is probably the user

    Attendee attendee;
    if (!incidence) {
        return attendee;
    }

    const Attendee::List attendees = incidence->attendees();
    for (const auto &a : attendees) {
        if (iamAttendee(a)) {
            attendee = a;
            break;
        }
    }

    return attendee;
}

[[nodiscard]] static Attendee findAttendee(const Incidence::Ptr &incidence, const QString &email)
{
    // Search for an attendee by email address

    Attendee attendee;
    if (!incidence) {
        return attendee;
    }

    const Attendee::List attendees = incidence->attendees();
    for (const auto &a : attendees) {
        if (email == a.email()) {
            attendee = a;
            break;
        }
    }
    return attendee;
}

[[nodiscard]] static bool rsvpRequested(const Incidence::Ptr &incidence)
{
    if (!incidence) {
        return false;
    }

    // use a heuristic to determine if a response is requested.

    bool rsvp = true; // better send superfluously than not at all
    Attendee::List const attendees = incidence->attendees();
    Attendee::List::ConstIterator it;
    const Attendee::List::ConstIterator end(attendees.constEnd());
    for (it = attendees.constBegin(); it != end; ++it) {
        if (it == attendees.constBegin()) {
            rsvp = (*it).RSVP(); // use what the first one has
        } else {
            if ((*it).RSVP() != rsvp) {
                rsvp = true; // they differ, default
                break;
            }
        }
    }
    return rsvp;
}

[[nodiscard]] static QString rsvpRequestedStr(bool rsvpRequested, const QString &role)
{
    if (rsvpRequested) {
        if (role.isEmpty()) {
            return i18n("Your response is requested.");
        } else {
            return i18n("Your response as <b>%1</b> is requested.", role);
        }
    } else {
        if (role.isEmpty()) {
            return i18n("No response is necessary.");
        } else {
            return i18n("No response as <b>%1</b> is necessary.", role);
        }
    }
}

[[nodiscard]] static QString myStatusStr(const Incidence::Ptr &incidence)
{
    QString ret;
    const Attendee a = findMyAttendee(incidence);
    if (!a.isNull() && a.status() != Attendee::NeedsAction && a.status() != Attendee::Delegated) {
#if KCALENDARCORE_VERSION < QT_VERSION_CHECK(6, 30, 0)
        ret = i18n("(<b>Note</b>: the Organizer preset your response to <b>%1</b>)", KCalUtils::Stringify::attendeeStatus(a.status()));
#else
        ret = i18n("(<b>Note</b>: the Organizer preset your response to <b>%1</b>)", Attendee::statusName(a.status()));
#endif
    }
    return ret;
}

[[nodiscard]] static QVariantHash invitationNote(const QString &title, const QString &note, const QString &color)
{
    QVariantHash noteHash;
    if (note.isEmpty()) {
        return noteHash;
    }

    noteHash[QStringLiteral("color")] = color;
    noteHash[QStringLiteral("title")] = title;
    noteHash[QStringLiteral("note")] = note;
    return noteHash;
}

[[nodiscard]] static QString invitationDescriptionIncidence(const Incidence::Ptr &incidence)
{
    if (!incidence->description().isEmpty()) {
        // use description too
        if (!incidence->descriptionIsRich() && !incidence->description().startsWith(QLatin1StringView("<!DOCTYPE HTML"))) {
            return string2HTML(incidence->description());
        } else {
            QString descr;
            if (!incidence->description().startsWith(QLatin1StringView("<!DOCTYPE HTML"))) {
                descr = incidence->richDescription();
            } else {
                descr = incidence->description();
            }
            descr = cleanHtml(descr);
            return htmlAddTag(QStringLiteral("p"), std::move(descr));
        }
    }

    return QString();
}

[[nodiscard]] static bool slicesInterval(const Event::Ptr &event, const QDateTime &startDt, const QDateTime &endDt)
{
    QDateTime closestStart = event->dtStart();
    QDateTime closestEnd = event->dtEnd();
    if (event->recurs()) {
        if (!event->recurrence()->timesInInterval(startDt, endDt).isEmpty()) {
            // If there is a recurrence in this interval we know already that we slice.
            return true;
        }
        closestStart = event->recurrence()->getPreviousDateTime(startDt);
        if (event->hasEndDate()) {
            closestEnd = closestStart.addSecs(event->dtStart().secsTo(event->dtEnd()));
        }
    } else {
        if (!event->hasEndDate() && event->hasDuration()) {
            closestEnd = closestStart.addSecs(event->duration());
        }
    }

    if (!closestEnd.isValid()) {
        // All events without an ending still happen if they are
        // started.
        return closestStart <= startDt;
    }

    if (closestStart <= startDt) {
        // It starts before the interval and ends after the start of the interval.
        return closestEnd > startDt;
    }

    // Are start and end both in this interval?
    /* cppcheck-suppress knownConditionTrueFalse */
    return (closestStart >= startDt && closestStart <= endDt) && (closestEnd >= startDt && closestEnd <= endDt);
}

[[nodiscard]] static QVariantList eventsOnSameDays(const InvitationFormatterHelper *helper, const Event::Ptr &event)
{
    if (!event || !helper || !helper->calendar()) {
        return QVariantList();
    }

    QDateTime startDay = event->dtStart();
    QDateTime endDay = event->hasEndDate() ? event->dtEnd() : event->dtStart();
    startDay.setTime(QTime(0, 0, 0));
    endDay.setTime(QTime(23, 59, 59));

    Event::List const matchingEvents = helper->calendar()->events(startDay.date(), endDay.date(), QTimeZone::systemTimeZone());
    if (matchingEvents.isEmpty()) {
        return QVariantList();
    }

    QVariantList events;
    int count = 0;
    for (auto it = matchingEvents.cbegin(), end = matchingEvents.cend(); it != end && count < 50; ++it) {
        if ((*it)->schedulingID() == event->uid()) {
            // Exclude the same event from the list.
            continue;
        }
        if (!slicesInterval(*it, startDay, endDay)) {
            /* Calendar::events includes events that have a recurrence that is
             * "active" in the specified interval. Whether or not the event is actually
             * happening ( has a recurrence that falls into the interval ).
             * This appears to be done deliberately and not to be a bug so we additionally
             * check if the event is actually happening here. */
            continue;
        }
        ++count;
        QVariantHash ev;
        ev[QStringLiteral("summary")] = invitationSummary(*it);
        ev[QStringLiteral("dateTime")] = formatStartEnd((*it)->dtStart(), (*it)->dtEnd(), (*it)->allDay());
        events.push_back(ev);
    }
    if (count == 50) {
        /* Abort after 50 entries to limit resource usage */
        events.push_back({});
    }
    return events;
}

[[nodiscard]] static QVariantHash invitationDetailsEvent(InvitationFormatterHelper *helper, const Event::Ptr &event)
{
    // Invitation details are formatted into an HTML table
    if (!event) {
        return QVariantHash();
    }

    QVariantHash incidence;
    incidence[QStringLiteral("iconName")] = QStringLiteral("view-pim-calendar");
    incidence[QStringLiteral("summary")] = invitationSummary(event);
    incidence[QStringLiteral("location")] = invitationLocation(event);
    incidence[QStringLiteral("recurs")] = event->recurs();
#if KCALENDARCORE_VERSION < QT_VERSION_CHECK(6, 30, 0)
    incidence[QStringLiteral("recurrence")] = KCalUtils::IncidenceFormatter::recurrenceString(event);
#else
    incidence[QStringLiteral("recurrence")] = event->recurrenceDescription();
#endif
    incidence[QStringLiteral("isMultiDay")] = event->isMultiDay(QTimeZone::systemTimeZone());
    incidence[QStringLiteral("isAllDay")] = event->allDay();
    incidence[QStringLiteral("dateTime")] = formatStartEnd(event->dtStart(), event->dtEnd(), event->allDay());
    incidence[QStringLiteral("description")] = invitationDescriptionIncidence(event);

    incidence[QStringLiteral("checkCalendarButton")] =
        inviteButton(QStringLiteral("check_calendar"), i18n("Check my calendar"), QStringLiteral("go-jump-today"), helper);
    incidence[QStringLiteral("eventsOnSameDays")] = eventsOnSameDays(helper, event);

    return incidence;
}

QString formatStartEnd(const QDateTime &start, const QDateTime &end, bool isAllDay)
{
    QString tmpStr;
    // <startDate[time> [- <[endDate][Time]>]
    // The startDate is always printed.
    // If the event does float the time is omitted.
    //
    // If it has an end dateTime:
    // on the same day -> Only add end time.
    // if it floats also omit the time
    tmpStr += dateTimeToString(start, isAllDay, false);

    if (end.isValid()) {
        if (start.date() == end.date()) {
            // same day
            if (start.time().isValid()) {
                tmpStr += QLatin1StringView(" - ") + QLocale().toString(end.toLocalTime().time(), QLocale::ShortFormat);
            }
        } else {
            tmpStr += QLatin1StringView(" - ") + dateTimeToString(end, isAllDay, false);
        }
    }
    return tmpStr;
}

[[nodiscard]] static QVariantHash
invitationDetailsEvent(InvitationFormatterHelper *helper, const Event::Ptr &event, const Event::Ptr &oldevent, const ScheduleMessage::Ptr &message)
{
    if (!oldevent) {
        return invitationDetailsEvent(helper, event);
    }

    QVariantHash incidence;

    // Print extra info typically dependent on the iTIP
    if (message->method() == iTIPDeclineCounter) {
        incidence[QStringLiteral("note")] = invitationNote(QString(), i18n("Please respond again to the original proposal."), noteColor());
    }

    incidence[QStringLiteral("isDiff")] = true;
    incidence[QStringLiteral("iconName")] = QStringLiteral("view-pim-calendar");
    incidence[QStringLiteral("summary")] = htmlCompare(invitationSummary(event), invitationSummary(oldevent));
    incidence[QStringLiteral("location")] = htmlCompare(invitationLocation(event), invitationLocation(oldevent));
    incidence[QStringLiteral("recurs")] = event->recurs() || oldevent->recurs();
#if KCALENDARCORE_VERSION < QT_VERSION_CHECK(6, 30, 0)
    incidence[QStringLiteral("recurrence")] =
        htmlCompare(KCalUtils::IncidenceFormatter::recurrenceString(event), KCalUtils::IncidenceFormatter::recurrenceString(oldevent));
#else
    incidence[QStringLiteral("recurrence")] = htmlCompare(event->recurrenceDescription(), oldevent->recurrenceDescription());
#endif
    incidence[QStringLiteral("dateTime")] = htmlCompare(formatStartEnd(event->dtStart(), event->dtEnd(), event->allDay()),
                                                        formatStartEnd(oldevent->dtStart(), oldevent->dtEnd(), oldevent->allDay()));
    incidence[QStringLiteral("description")] = invitationDescriptionIncidence(event);

    incidence[QStringLiteral("checkCalendarButton")] =
        inviteButton(QStringLiteral("check_calendar"), i18n("Check my calendar"), QStringLiteral("go-jump-today"), helper);
    incidence[QStringLiteral("eventsOnSameDays")] = eventsOnSameDays(helper, event);

    return incidence;
}

[[nodiscard]] static QVariantHash invitationDetailsTodo(const Todo::Ptr &todo)
{
    // To-do details are formatted into an HTML table
    if (!todo) {
        return QVariantHash();
    }

    QVariantHash incidence;
    incidence[QStringLiteral("iconName")] = QStringLiteral("view-pim-tasks");
    incidence[QStringLiteral("summary")] = invitationSummary(todo);
    incidence[QStringLiteral("location")] = invitationLocation(todo);
    incidence[QStringLiteral("isAllDay")] = todo->allDay();
    incidence[QStringLiteral("hasStartDate")] = todo->hasStartDate();
    bool isMultiDay = false;
    if (todo->hasStartDate()) {
        if (todo->allDay()) {
            incidence[QStringLiteral("dtStartStr")] = QLocale().toString(todo->dtStart().toLocalTime().date(), QLocale::ShortFormat);
        } else {
            incidence[QStringLiteral("dtStartStr")] = QLocale().toString(todo->dtStart(), QLocale::ShortFormat);
        }
        isMultiDay = todo->dtStart().date() != todo->dtDue().date();
    }
    if (todo->allDay()) {
        incidence[QStringLiteral("dtDueStr")] = QLocale().toString(todo->dtDue().toLocalTime().date(), QLocale::ShortFormat);
    } else {
        incidence[QStringLiteral("dtDueStr")] = QLocale().toString(todo->dtDue(), QLocale::ShortFormat);
    }
    incidence[QStringLiteral("isMultiDay")] = isMultiDay;
    if (todo->percentComplete() > 0) {
        incidence[QStringLiteral("percentComplete")] = i18n("%1%", todo->percentComplete());
    }
    incidence[QStringLiteral("recurs")] = todo->recurs();
#if KCALENDARCORE_VERSION < QT_VERSION_CHECK(6, 30, 0)
    incidence[QStringLiteral("recurrence")] = KCalUtils::IncidenceFormatter::recurrenceString(todo);
#else
    incidence[QStringLiteral("recurrence")] = todo->recurrenceDescription();
#endif
    incidence[QStringLiteral("description")] = invitationDescriptionIncidence(todo);

    return incidence;
}

[[nodiscard]] static QVariantHash invitationDetailsTodo(const Todo::Ptr &todo, const Todo::Ptr &oldtodo, const ScheduleMessage::Ptr &message)
{
    if (!oldtodo) {
        return invitationDetailsTodo(todo);
    }

    QVariantHash incidence;

    // Print extra info typically dependent on the iTIP
    if (message->method() == iTIPDeclineCounter) {
        incidence[QStringLiteral("note")] = invitationNote(QString(), i18n("Please respond again to the original proposal."), noteColor());
    }

    incidence[QStringLiteral("iconName")] = QStringLiteral("view-pim-tasks");
    incidence[QStringLiteral("isDiff")] = true;
    incidence[QStringLiteral("summary")] = htmlCompare(invitationSummary(todo), invitationSummary(oldtodo));
    incidence[QStringLiteral("location")] = htmlCompare(invitationLocation(todo), invitationLocation(oldtodo));
    incidence[QStringLiteral("isAllDay")] = todo->allDay();
    incidence[QStringLiteral("hasStartDate")] = todo->hasStartDate();
    incidence[QStringLiteral("dtStartStr")] = htmlCompare(dateTimeToString(todo->dtStart(), false, false), dateTimeToString(oldtodo->dtStart(), false, false));
    incidence[QStringLiteral("dtDueStr")] = htmlCompare(dateTimeToString(todo->dtDue(), false, false), dateTimeToString(oldtodo->dtDue(), false, false));
    incidence[QStringLiteral("percentComplete")] = htmlCompare(i18n("%1%", todo->percentComplete()), i18n("%1%", oldtodo->percentComplete()));

    incidence[QStringLiteral("recurs")] = todo->recurs() || oldtodo->recurs();
#if KCALENDARCORE_VERSION < QT_VERSION_CHECK(6, 30, 0)
    incidence[QStringLiteral("recurrence")] =
        htmlCompare(KCalUtils::IncidenceFormatter::recurrenceString(todo), KCalUtils::IncidenceFormatter::recurrenceString(oldtodo));
#else
    incidence[QStringLiteral("recurrence")] = htmlCompare(todo->recurrenceDescription(), oldtodo->recurrenceDescription());
#endif
    incidence[QStringLiteral("description")] = invitationDescriptionIncidence(todo);

    return incidence;
}

[[nodiscard]] static QVariantHash invitationDetailsJournal(const Journal::Ptr &journal)
{
    if (!journal) {
        return QVariantHash();
    }

    QVariantHash incidence;
    incidence[QStringLiteral("iconName")] = QStringLiteral("view-pim-journal");
    incidence[QStringLiteral("summary")] = invitationSummary(journal);
    incidence[QStringLiteral("date")] = journal->dtStart();
    incidence[QStringLiteral("description")] = invitationDescriptionIncidence(journal);

    return incidence;
}

[[nodiscard]] static QVariantHash invitationDetailsJournal(const Journal::Ptr &journal, const Journal::Ptr &oldjournal)
{
    if (!oldjournal) {
        return invitationDetailsJournal(journal);
    }

    QVariantHash incidence;
    incidence[QStringLiteral("iconName")] = QStringLiteral("view-pim-journal");
    incidence[QStringLiteral("summary")] = htmlCompare(invitationSummary(journal), invitationSummary(oldjournal));
    incidence[QStringLiteral("dateStr")] = htmlCompare(QLocale().toString(journal->dtStart().toLocalTime().date(), QLocale::LongFormat),
                                                       QLocale().toString(oldjournal->dtStart().toLocalTime().date(), QLocale::LongFormat));
    incidence[QStringLiteral("description")] = invitationDescriptionIncidence(journal);

    return incidence;
}

[[nodiscard]] static QVariantHash invitationDetailsFreeBusy(const FreeBusy::Ptr &fb)
{
    if (!fb) {
        return QVariantHash();
    }

    QVariantHash incidence;
    incidence[QStringLiteral("organizer")] = fb->organizer().fullName();
    incidence[QStringLiteral("dtStart")] = fb->dtStart();
    incidence[QStringLiteral("dtEnd")] = fb->dtEnd();

    QVariantList periodsList;
    const Period::List periods = fb->busyPeriods();
    for (auto it = periods.cbegin(), end = periods.cend(); it != end; ++it) {
        QVariantHash period;
        period[QStringLiteral("hasDuration")] = it->hasDuration();
        if (it->hasDuration()) {
            std::chrono::milliseconds dur = std::chrono::seconds(it->duration().asSeconds());
            KFormat f;
            period[QStringLiteral("duration")] = f.formatSpelloutDuration(dur.count());
        }
        period[QStringLiteral("start")] = it->start();
        period[QStringLiteral("end")] = it->end();

        periodsList.push_back(period);
    }
    incidence[QStringLiteral("periods")] = periodsList;

    return incidence;
}

[[nodiscard]] static QVariantHash invitationDetailsFreeBusy(const FreeBusy::Ptr &fb, [[maybe_unused]] const FreeBusy::Ptr &oldfb)
{
    return invitationDetailsFreeBusy(fb);
}

[[nodiscard]] static QString
invitationHeaderEvent(const Event::Ptr &event, const Incidence::Ptr &existingIncidence, const ScheduleMessage::Ptr &msg, const QString &sender)
{
    if (!msg || !event) {
        return QString();
    }

    switch (msg->method()) {
    case iTIPPublish:
        return i18n("This invitation has been published.");
    case iTIPRequest:
        if (existingIncidence && event->revision() > 0) {
            QString const orgStr = organizerName(event, sender);
            if (senderIsOrganizer(event, sender)) {
                return i18n("This invitation has been updated by the organizer %1.", orgStr);
            } else {
                return i18n("This invitation has been updated by %1 as a representative of %2.", sender, orgStr);
            }
        }
        if (iamOrganizer(event)) {
            return i18n("I created this invitation.");
        } else {
            QString const orgStr = organizerName(event, sender);
            if (senderIsOrganizer(event, sender)) {
                return i18n("You received an invitation from %1.", orgStr);
            } else {
                return i18n("You received an invitation from %1 as a representative of %2.", sender, orgStr);
            }
        }
    case iTIPRefresh:
        return i18n("This invitation was refreshed.");
    case iTIPCancel:
        if (iamOrganizer(event)) {
            return i18n("This invitation has been canceled.");
        } else {
            return i18n("The organizer has revoked the invitation.");
        }
    case iTIPAdd:
        return i18n("Addition to the invitation.");
    case iTIPReply: {
        Attendee::List attendees = event->attendees();
        if (attendees.isEmpty()) {
            qDebug() << "No attendees in the iCal reply!";
            return QString();
        }
        if (attendees.count() != 1) {
            qDebug() << "Warning: attendeecount in the reply should be 1" << "but is" << attendees.count();
        }
        QString const attendeeName = firstAttendeeName(event, sender);

        QString delegatorName;
        QString dummyName;
        const Attendee attendee = *attendees.begin();
        KEmailAddress::extractEmailAddressAndName(attendee.delegator(), dummyName, delegatorName);
        if (delegatorName.isEmpty()) {
            delegatorName = attendee.delegator();
        }

        switch (attendee.status()) {
        case Attendee::NeedsAction:
            return i18n("%1 indicates this invitation still needs some action.", attendeeName);
        case Attendee::Accepted:
            if (event->revision() > 0) {
                if (!sender.isEmpty()) {
                    return i18n("This invitation has been updated by attendee %1.", sender);
                } else {
                    return i18n("This invitation has been updated by an attendee.");
                }
            } else {
                if (delegatorName.isEmpty()) {
                    return i18n("%1 accepts this invitation.", attendeeName);
                } else {
                    return i18n("%1 accepts this invitation on behalf of %2.", attendeeName, delegatorName);
                }
            }
        case Attendee::Tentative:
            if (delegatorName.isEmpty()) {
                return i18n("%1 tentatively accepts this invitation.", attendeeName);
            } else {
                return i18n("%1 tentatively accepts this invitation on behalf of %2.", attendeeName, delegatorName);
            }
        case Attendee::Declined:
            if (delegatorName.isEmpty()) {
                return i18n("%1 declines this invitation.", attendeeName);
            } else {
                return i18n("%1 declines this invitation on behalf of %2.", attendeeName, delegatorName);
            }
        case Attendee::Delegated: {
            QString delegate;
            QString dummy;
            KEmailAddress::extractEmailAddressAndName(attendee.delegate(), dummy, delegate);
            if (delegate.isEmpty()) {
                delegate = attendee.delegate();
            }
            if (!delegate.isEmpty()) {
                return i18n("%1 has delegated this invitation to %2.", attendeeName, delegate);
            } else {
                return i18n("%1 has delegated this invitation.", attendeeName);
            }
        }
        case Attendee::Completed:
            return i18n("This invitation is now completed.");
        case Attendee::InProcess:
            return i18n("%1 is still processing the invitation.", attendeeName);
        case Attendee::None:
            return i18n("Unknown response to this invitation.");
        }
        break;
    }
    case iTIPCounter:
        return i18n("%1 makes this counter proposal.", firstAttendeeName(event, i18n("Sender")));

    case iTIPDeclineCounter: {
        QString const orgStr = organizerName(event, sender);
        if (senderIsOrganizer(event, sender)) {
            return i18n("%1 declines your counter proposal.", orgStr);
        } else {
            return i18n("%1 declines your counter proposal on behalf of %2.", sender, orgStr);
        }
    }

    case iTIPNoMethod:
        return i18n("Error: Event iTIP message with unknown method.");
    }
    qCritical() << "encountered an iTIP method that we do not support.";
    return QString();
}

[[nodiscard]] static QString
invitationHeaderTodo(const Todo::Ptr &todo, const Incidence::Ptr &existingIncidence, const ScheduleMessage::Ptr &msg, const QString &sender)
{
    if (!msg || !todo) {
        return QString();
    }

    switch (msg->method()) {
    case iTIPPublish:
        return i18n("This to-do has been published.");
    case iTIPRequest:
        if (existingIncidence && todo->revision() > 0) {
            QString const orgStr = organizerName(todo, sender);
            if (senderIsOrganizer(todo, sender)) {
                return i18n("This to-do has been updated by the organizer %1.", orgStr);
            } else {
                return i18n("This to-do has been updated by %1 as a representative of %2.", sender, orgStr);
            }
        } else {
            if (iamOrganizer(todo)) {
                return i18n("I created this to-do.");
            } else {
                QString const orgStr = organizerName(todo, sender);
                if (senderIsOrganizer(todo, sender)) {
                    return i18n("You have been assigned this to-do by %1.", orgStr);
                } else {
                    return i18n("You have been assigned this to-do by %1 as a representative of %2.", sender, orgStr);
                }
            }
        }
    case iTIPRefresh:
        return i18n("This to-do was refreshed.");
    case iTIPCancel:
        if (iamOrganizer(todo)) {
            return i18n("This to-do was canceled.");
        } else {
            return i18n("The organizer has revoked this to-do.");
        }
    case iTIPAdd:
        return i18n("Addition to the to-do.");
    case iTIPReply: {
        Attendee::List attendees = todo->attendees();
        if (attendees.isEmpty()) {
            qDebug() << "No attendees in the iCal reply!";
            return QString();
        }
        if (attendees.count() != 1) {
            qDebug() << "Warning: attendeecount in the reply should be 1." << "but is" << attendees.count();
        }
        QString const attendeeName = firstAttendeeName(todo, sender);

        QString delegatorName;
        QString dummyName;
        const Attendee attendee = *attendees.begin();
        KEmailAddress::extractEmailAddressAndName(attendee.delegator(), dummyName, delegatorName);
        if (delegatorName.isEmpty()) {
            delegatorName = attendee.delegator();
        }

        switch (attendee.status()) {
        case Attendee::NeedsAction:
            return i18n("%1 indicates this to-do assignment still needs some action.", attendeeName);
        case Attendee::Accepted:
            if (todo->revision() > 0) {
                if (!sender.isEmpty()) {
                    if (todo->isCompleted()) {
                        return i18n("This to-do has been completed by assignee %1.", sender);
                    } else {
                        return i18n("This to-do has been updated by assignee %1.", sender);
                    }
                } else {
                    if (todo->isCompleted()) {
                        return i18n("This to-do has been completed by an assignee.");
                    } else {
                        return i18n("This to-do has been updated by an assignee.");
                    }
                }
            } else {
                if (delegatorName.isEmpty()) {
                    return i18n("%1 accepts this to-do.", attendeeName);
                } else {
                    return i18n("%1 accepts this to-do on behalf of %2.", attendeeName, delegatorName);
                }
            }
        case Attendee::Tentative:
            if (delegatorName.isEmpty()) {
                return i18n("%1 tentatively accepts this to-do.", attendeeName);
            } else {
                return i18n("%1 tentatively accepts this to-do on behalf of %2.", attendeeName, delegatorName);
            }
        case Attendee::Declined:
            if (delegatorName.isEmpty()) {
                return i18n("%1 declines this to-do.", attendeeName);
            } else {
                return i18n("%1 declines this to-do on behalf of %2.", attendeeName, delegatorName);
            }
        case Attendee::Delegated: {
            QString delegate;
            QString dummy;
            KEmailAddress::extractEmailAddressAndName(attendee.delegate(), dummy, delegate);
            if (delegate.isEmpty()) {
                delegate = attendee.delegate();
            }
            if (!delegate.isEmpty()) {
                return i18n("%1 has delegated this to-do to %2.", attendeeName, delegate);
            } else {
                return i18n("%1 has delegated this to-do.", attendeeName);
            }
        }
        case Attendee::Completed:
            return i18n("The request for this to-do is now completed.");
        case Attendee::InProcess:
            return i18n("%1 is still processing the to-do.", attendeeName);
        case Attendee::None:
            return i18n("Unknown response to this to-do.");
        }
        break;
    }
    case iTIPCounter:
        return i18n("%1 makes this counter proposal.", firstAttendeeName(todo, sender));

    case iTIPDeclineCounter: {
        const QString orgStr = organizerName(todo, sender);
        if (senderIsOrganizer(todo, sender)) {
            return i18n("%1 declines the counter proposal.", orgStr);
        } else {
            return i18n("%1 declines the counter proposal on behalf of %2.", sender, orgStr);
        }
    }

    case iTIPNoMethod:
        return i18n("Error: To-do iTIP message with unknown method.");
    }
    qCritical() << "encountered an iTIP method that we do not support";
    return QString();
}

[[nodiscard]] static QString invitationHeaderJournal(const Journal::Ptr &journal, const ScheduleMessage::Ptr &msg)
{
    if (!msg || !journal) {
        return QString();
    }

    switch (msg->method()) {
    case iTIPPublish:
        return i18n("This journal has been published.");
    case iTIPRequest:
        return i18n("You have been assigned this journal.");
    case iTIPRefresh:
        return i18n("This journal was refreshed.");
    case iTIPCancel:
        return i18n("This journal was canceled.");
    case iTIPAdd:
        return i18n("Addition to the journal.");
    case iTIPReply: {
        Attendee::List attendees = journal->attendees();
        if (attendees.isEmpty()) {
            qDebug() << "No attendees in the iCal reply!";
            return QString();
        }
        if (attendees.count() != 1) {
            qDebug() << "Warning: attendeecount in the reply should be 1 " << "but is " << attendees.count();
        }
        const Attendee attendee = *attendees.begin();

        switch (attendee.status()) {
        case Attendee::NeedsAction:
            return i18n("Sender indicates this journal assignment still needs some action.");
        case Attendee::Accepted:
            return i18n("Sender accepts this journal.");
        case Attendee::Tentative:
            return i18n("Sender tentatively accepts this journal.");
        case Attendee::Declined:
            return i18n("Sender declines this journal.");
        case Attendee::Delegated:
            return i18n("Sender has delegated this request for the journal.");
        case Attendee::Completed:
            return i18n("The request for this journal is now completed.");
        case Attendee::InProcess:
            return i18n("Sender is still processing the invitation.");
        case Attendee::None:
            return i18n("Unknown response to this journal.");
        }
        break;
    }
    case iTIPCounter:
        return i18n("Sender makes this counter proposal.");
    case iTIPDeclineCounter:
        return i18n("Sender declines the counter proposal.");
    case iTIPNoMethod:
        return i18n("Error: Journal iTIP message with unknown method.");
    }
    qCritical() << "encountered an iTIP method that we do not support";
    return QString();
}

[[nodiscard]] static QString invitationHeaderFreeBusy(const FreeBusy::Ptr &fb, const ScheduleMessage::Ptr &msg)
{
    if (!msg || !fb) {
        return QString();
    }

    switch (msg->method()) {
    case iTIPPublish:
        return i18n("This free/busy list has been published.");
    case iTIPRequest:
        return i18n("The free/busy list has been requested.");
    case iTIPRefresh:
        return i18n("This free/busy list was refreshed.");
    case iTIPCancel:
        return i18n("This free/busy list was canceled.");
    case iTIPAdd:
        return i18n("Addition to the free/busy list.");
    case iTIPReply:
        return i18n("Reply to the free/busy list.");
    case iTIPCounter:
        return i18n("Sender makes this counter proposal.");
    case iTIPDeclineCounter:
        return i18n("Sender declines the counter proposal.");
    case iTIPNoMethod:
        return i18n("Error: Free/Busy iTIP message with unknown method.");
    }
    qCritical() << "encountered an iTIP method that we do not support";
    return QString();
}

//@endcond

[[nodiscard]] static QVariantList invitationAttendeeList(const Incidence::Ptr &incidence)
{
    if (!incidence) {
        return QVariantList();
    }

    QVariantList attendees;
    const Attendee::List lstAttendees = incidence->attendees();
    for (const Attendee &a : lstAttendees) {
        if (iamAttendee(a)) {
            continue;
        }

        QVariantHash attendee;
        attendee[QStringLiteral("name")] = a.name();
        attendee[QStringLiteral("email")] = a.email();
        attendee[QStringLiteral("delegator")] = a.delegator();
        attendee[QStringLiteral("delegate")] = a.delegate();
        attendee[QStringLiteral("isOrganizer")] = attendeeIsOrganizer(incidence, a);
#if KCALENDARCORE_VERSION < QT_VERSION_CHECK(6, 30, 0)
        attendee[QStringLiteral("status")] = KCalUtils::Stringify::attendeeStatus(a.status());
#else
        attendee[QStringLiteral("status")] = Attendee::statusName(a.status());
#endif
        attendee[QStringLiteral("icon")] = rsvpStatusIconName(a.status());

        attendees.push_back(attendee);
    }

    return attendees;
}

[[nodiscard]] static QVariantList invitationRsvpList(const Incidence::Ptr &incidence, const Attendee &sender)
{
    if (!incidence) {
        return QVariantList();
    }

    QVariantList attendees;
    const Attendee::List lstAttendees = incidence->attendees();
    for (const Attendee &a_ : lstAttendees) {
        Attendee a = a_;
        if (!attendeeIsOrganizer(incidence, a)) {
            continue;
        }
        QVariantHash attendee;
#if KCALENDARCORE_VERSION < QT_VERSION_CHECK(6, 30, 0)
        attendee[QStringLiteral("status")] = KCalUtils::Stringify::attendeeStatus(a.status());
#else
        attendee[QStringLiteral("status")] = Attendee::statusName(a.status());
#endif
        if (!sender.isNull() && (a.email() == sender.email())) {
            // use the attendee taken from the response incidence,
            // rather than the attendee from the calendar incidence.
            if (a.status() != sender.status()) {
#if KCALENDARCORE_VERSION < QT_VERSION_CHECK(6, 30, 0)
                attendee[QStringLiteral("status")] = i18n("%1 (<i>unrecorded</i>)", KCalUtils::Stringify::attendeeStatus(sender.status()));
#else
                attendee[QStringLiteral("status")] = i18n("%1 (<i>unrecorded</i>)", Attendee::statusName(sender.status()));
#endif
            }
            a = sender;
        }

        attendee[QStringLiteral("name")] = a.name();
        attendee[QStringLiteral("email")] = a.email();
        attendee[QStringLiteral("delegator")] = a.delegator();
        attendee[QStringLiteral("delegate")] = a.delegate();
        attendee[QStringLiteral("isOrganizer")] = attendeeIsOrganizer(incidence, a);
        attendee[QStringLiteral("isMyself")] = iamAttendee(a);
        attendee[QStringLiteral("icon")] = rsvpStatusIconName(a.status());

        attendees.push_back(attendee);
    }

    return attendees;
}

[[nodiscard]] static QVariantList invitationAttachments(const Incidence::Ptr &incidence, InvitationFormatterHelper *helper)
{
    if (!incidence) {
        return QVariantList();
    }

    if (incidence->type() == Incidence::TypeFreeBusy) {
        // A FreeBusy does not have a valid attachment due to the static-cast from IncidenceBase
        return QVariantList();
    }

    QVariantList attachments;
    QMimeDatabase const mimeDb;
    const Attachment::List lstAttachments = incidence->attachments();
    for (const Attachment &a : lstAttachments) {
        QVariantHash attachment;
        auto mimeType = mimeDb.mimeTypeForName(a.mimeType());
        attachment[QStringLiteral("icon")] = (mimeType.isValid() ? mimeType.iconName() : QStringLiteral("application-octet-stream"));
        attachment[QStringLiteral("name")] = a.label();
        const QString attachementStr = helper->generateLinkURL(QStringLiteral("ATTACH:%1").arg(QString::fromLatin1(a.label().toUtf8().toBase64())));
        attachment[QStringLiteral("uri")] = attachementStr;
        attachments.push_back(attachment);
    }

    return attachments;
}

//@cond PRIVATE
template<typename T>
class ItipFormatter::ScheduleMessageVisitor : public Visitor
{
public:
    bool act(const IncidenceBase::Ptr &incidence, const Incidence::Ptr &existingIncidence, const ScheduleMessage::Ptr &msg, const QString &sender)
    {
        mExistingIncidence = existingIncidence;
        mMessage = msg;
        mSender = sender;
        return incidence->accept(*this, incidence);
    }

    [[nodiscard]] const T &result() const
    {
        return mResult;
    }

    [[nodiscard]] T takeResult()
    {
        return std::move(mResult);
    }

protected:
    T mResult;
    Incidence::Ptr mExistingIncidence;
    ScheduleMessage::Ptr mMessage;
    QString mSender;
};

class ItipFormatter::InvitationHeaderVisitor : public ItipFormatter::ScheduleMessageVisitor<QString>
{
protected:
    bool visit(const Event::Ptr &event) override
    {
        mResult = invitationHeaderEvent(event, mExistingIncidence, mMessage, mSender);
        return !mResult.isEmpty();
    }

    bool visit(const Todo::Ptr &todo) override
    {
        mResult = invitationHeaderTodo(todo, mExistingIncidence, mMessage, mSender);
        return !mResult.isEmpty();
    }

    bool visit(const Journal::Ptr &journal) override
    {
        mResult = invitationHeaderJournal(journal, mMessage);
        return !mResult.isEmpty();
    }

    bool visit(const FreeBusy::Ptr &fb) override
    {
        mResult = invitationHeaderFreeBusy(fb, mMessage);
        return !mResult.isEmpty();
    }
};

class ItipFormatter::InvitationBodyVisitor : public ItipFormatter::ScheduleMessageVisitor<QVariantHash>
{
public:
    explicit InvitationBodyVisitor(InvitationFormatterHelper *helper)
        : ScheduleMessageVisitor()
        , mHelper(helper)
    {
    }

protected:
    bool visit(const Event::Ptr &event) override
    {
        Event::Ptr const oldevent = mExistingIncidence.dynamicCast<Event>();
        mResult = invitationDetailsEvent(mHelper, event, oldevent, mMessage);
        return !mResult.isEmpty();
    }

    bool visit(const Todo::Ptr &todo) override
    {
        Todo::Ptr const oldtodo = mExistingIncidence.dynamicCast<Todo>();
        mResult = invitationDetailsTodo(todo, oldtodo, mMessage);
        return !mResult.isEmpty();
    }

    bool visit(const Journal::Ptr &journal) override
    {
        Journal::Ptr const oldjournal = mExistingIncidence.dynamicCast<Journal>();
        mResult = invitationDetailsJournal(journal, oldjournal);
        return !mResult.isEmpty();
    }

    bool visit(const FreeBusy::Ptr &fb) override
    {
        mResult = invitationDetailsFreeBusy(fb, FreeBusy::Ptr());
        return !mResult.isEmpty();
    }

private:
    InvitationFormatterHelper *mHelper;
};
//@endcond

class InvitationFormatterHelperPrivate
{
};

InvitationFormatterHelper::InvitationFormatterHelper()
    : d(nullptr)
{
}

InvitationFormatterHelper::~InvitationFormatterHelper()
{
}

QString InvitationFormatterHelper::generateLinkURL(const QString &id)
{
    return id;
}

QString InvitationFormatterHelper::makeLink(const QString &id, const QString &text)
{
    if (!id.startsWith(QLatin1StringView("ATTACH:"))) {
        const QString res = QStringLiteral("<a href=\"%1\"><font size=\"-1\"><b>%2</b></font></a>").arg(generateLinkURL(id), text);
        return res;
    } else {
        // draw the attachment links in non-bold face
        const QString res = QStringLiteral("<a href=\"%1\">%2</a>").arg(generateLinkURL(id), text);
        return res;
    }
}

// Check if the given incidence is likely one that we own instead one from
// a shared calendar (Kolab-specific)
static bool incidenceOwnedByMe([[maybe_unused]] const Calendar::Ptr &calendar, [[maybe_unused]] const Incidence::Ptr &incidence)
{
    return true;
}

static QVariantHash inviteButton(const QString &id, const QString &text, const QString &iconName, InvitationFormatterHelper *helper)
{
    QVariantHash button;
    button[QStringLiteral("uri")] = helper->generateLinkURL(id);
    button[QStringLiteral("icon")] = iconName;
    button[QStringLiteral("label")] = text;
    return button;
}

static QVariantList responseButtons(const Incidence::Ptr &incidence,
                                    bool rsvpReq,
                                    bool rsvpRec,
                                    InvitationFormatterHelper *helper,
                                    const Incidence::Ptr &existingInc = Incidence::Ptr())
{
    bool hideAccept = false;
    bool hideTentative = false;
    bool hideDecline = false;

    if (existingInc) {
        const Attendee ea = findMyAttendee(existingInc);
        if (!ea.isNull()) {
            // If this is an update of an already accepted incidence
            // to not show the buttons that confirm the status.
            hideAccept = ea.status() == Attendee::Accepted;
            hideDecline = ea.status() == Attendee::Declined;
            hideTentative = ea.status() == Attendee::Tentative;
        }
    }

    QVariantList buttons;
    if (!rsvpReq && (incidence && incidence->revision() == 0)) {
        // Record only
        buttons << inviteButton(QStringLiteral("record"), i18n("Record"), QStringLiteral("dialog-ok"), helper);

        // Move to trash
        buttons << inviteButton(QStringLiteral("delete"), i18n("Move to Trash"), QStringLiteral("edittrash"), helper);
    } else {
        // Accept
        if (!hideAccept) {
            buttons << inviteButton(QStringLiteral("accept"), i18nc("accept invitation", "Accept"), QStringLiteral("dialog-ok-apply"), helper);
        }

        // Tentative
        if (!hideTentative) {
            buttons << inviteButton(QStringLiteral("accept_conditionally"),
                                    i18nc("Accept invitation conditionally", "Tentative"),
                                    QStringLiteral("dialog-ok"),
                                    helper);
        }

        // Decline
        if (!hideDecline) {
            buttons << inviteButton(QStringLiteral("decline"), i18nc("decline invitation", "Decline"), QStringLiteral("dialog-cancel"), helper);
        }

        // Counter proposal
        buttons << inviteButton(QStringLiteral("counter"), i18nc("invitation counter proposal", "Counter proposal ..."), QStringLiteral("edit-undo"), helper);
    }

    if (!rsvpRec || (incidence && incidence->revision() > 0)) {
        // Delegate
        buttons << inviteButton(QStringLiteral("delegate"), i18nc("delegate invitation to another", "Delegate ..."), QStringLiteral("mail-forward"), helper);
    }
    return buttons;
}

[[nodiscard]] static QVariantList counterButtons(InvitationFormatterHelper *helper)
{
    QVariantList buttons;

    // Accept proposal
    buttons << inviteButton(QStringLiteral("accept_counter"), i18n("Accept"), QStringLiteral("dialog-ok-apply"), helper);

    // Decline proposal
    buttons << inviteButton(QStringLiteral("decline_counter"), i18n("Decline"), QStringLiteral("dialog-cancel"), helper);

    return buttons;
}

[[nodiscard]] static QVariantList recordButtons(const Incidence::Ptr &incidence, InvitationFormatterHelper *helper)
{
    QVariantList buttons;
    if (incidence) {
        buttons << inviteButton(QStringLiteral("reply"),
                                incidence->type() == Incidence::TypeTodo ? i18n("Record invitation in my to-do list")
                                                                         : i18n("Record invitation in my calendar"),
                                QStringLiteral("dialog-ok"),
                                helper);
    }
    return buttons;
}

[[nodiscard]] static QVariantList recordResponseButtons(const Incidence::Ptr &incidence, InvitationFormatterHelper *helper)
{
    QVariantList buttons;

    if (incidence) {
        buttons << inviteButton(QStringLiteral("reply"),
                                incidence->type() == Incidence::TypeTodo ? i18n("Record response in my to-do list") : i18n("Record response in my calendar"),
                                QStringLiteral("dialog-ok"),
                                helper);
    }
    return buttons;
}

[[nodiscard]] static QVariantList cancelButtons(const Incidence::Ptr &incidence, InvitationFormatterHelper *helper)
{
    QVariantList buttons;

    // Remove invitation
    if (incidence) {
        buttons << inviteButton(QStringLiteral("cancel"),
                                incidence->type() == Incidence::TypeTodo ? i18n("Remove invitation from my to-do list")
                                                                         : i18n("Remove invitation from my calendar"),
                                QStringLiteral("dialog-cancel"),
                                helper);
    }

    return buttons;
}

[[nodiscard]] static QVariantHash invitationStyle()
{
    QVariantHash style;
    QPalette p;
    p.setCurrentColorGroup(QPalette::Normal);
    style[QStringLiteral("buttonBg")] = p.color(QPalette::Button).name();
    style[QStringLiteral("buttonBorder")] = p.shadow().color().name();
    style[QStringLiteral("buttonFg")] = p.color(QPalette::ButtonText).name();
    return style;
}

Calendar::Ptr InvitationFormatterHelper::calendar() const
{
    return Calendar::Ptr();
}

QString ItipFormatter::formatICalInvitation(const KCalendarCore::ScheduleMessage::Ptr &message, InvitationFormatterHelper *helper, const QString &sender)
{
    IncidenceBase::Ptr const incBase = message->event();

    // Determine if this incidence is in my calendar (and owned by me)
    Incidence::Ptr existingIncidence;
    if (incBase && helper->calendar()) {
        existingIncidence = helper->calendar()->incidence(incBase->uid(), incBase->recurrenceId());

        /* cppcheck-suppress knownConditionTrueFalse */
        if (!incidenceOwnedByMe(helper->calendar(), existingIncidence)) {
            existingIncidence.clear();
        }
        if (!existingIncidence) {
            const Incidence::List list = helper->calendar()->incidences();
            for (Incidence::List::ConstIterator it = list.begin(), end = list.end(); it != end; ++it) {
                /* cppcheck-suppress knownConditionTrueFalse */
                if ((*it)->schedulingID() == incBase->uid() && incidenceOwnedByMe(helper->calendar(), *it)
                    && (*it)->recurrenceId() == incBase->recurrenceId()) {
                    existingIncidence = *it;
                    break;
                }
            }
        }
    }

    Incidence::Ptr const inc = incBase.staticCast<Incidence>(); // the incidence in the invitation email

    // If the IncidenceBase is a FreeBusy, then we cannot access the revision number in
    // the static-casted Incidence; so for sake of nothing better use 0 as the revision.
    int incRevision = 0;
    if (inc && inc->type() != Incidence::TypeFreeBusy) {
        incRevision = inc->revision();
    }

    ItipFormatter::InvitationHeaderVisitor headerVisitor;
    // The InvitationHeaderVisitor returns false if the incidence is somehow invalid, or not handled
    if (!headerVisitor.act(inc, existingIncidence, message, sender)) {
        return QString();
    }

    QVariantHash incidence;

    // use the Outlook 2007 Comparison Style
    ItipFormatter::InvitationBodyVisitor bodyVisitor(helper);
    bool bodyOk;
    if (message->method() == iTIPRequest || message->method() == iTIPReply || message->method() == iTIPDeclineCounter) {
        if (inc && existingIncidence && incRevision < existingIncidence->revision()) {
            bodyOk = bodyVisitor.act(existingIncidence, inc, message, sender);
        } else {
            bodyOk = bodyVisitor.act(inc, existingIncidence, message, sender);
        }
    } else {
        bodyOk = bodyVisitor.act(inc, Incidence::Ptr(), message, sender);
    }
    if (!bodyOk) {
        return QString();
    }

    incidence = bodyVisitor.takeResult();
    incidence[QStringLiteral("style")] = invitationStyle();
    incidence[QStringLiteral("ltr")] = QApplication::isRightToLeft() ? QStringLiteral("rtl") : QStringLiteral("ltr");
    incidence[QStringLiteral("head")] = headerVisitor.result();

    // determine if I am the organizer for this invitation
    bool const myInc = iamOrganizer(inc);

    // determine if the invitation response has already been recorded
    bool rsvpRec = false;
    Attendee eattendee;
    if (!myInc) {
        Incidence::Ptr rsvpIncidence = existingIncidence;
        if (!rsvpIncidence && inc && incRevision > 0) {
            rsvpIncidence = inc;
        }
        if (rsvpIncidence) {
            eattendee = findMyAttendee(rsvpIncidence);
        }
        if (!eattendee.isNull()
            && (eattendee.status() == Attendee::Accepted || eattendee.status() == Attendee::Declined || eattendee.status() == Attendee::Tentative)) {
            rsvpRec = true;
        }
    }

    // determine invitation role
    QString role;
    bool isDelegated = false;
    Attendee firstAtt = findMyAttendee(inc);
    if (firstAtt.isNull() && inc) {
        if (!inc->attendees().isEmpty()) {
            firstAtt = inc->attendees().at(0);
        }
    }
    if (!firstAtt.isNull()) {
        isDelegated = (firstAtt.status() == Attendee::Delegated);
#if KCALENDARCORE_VERSION < QT_VERSION_CHECK(6, 30, 0)
        role = KCalUtils::Stringify::attendeeRole(firstAtt.role());
#else
        role = Attendee::roleName(firstAtt.role());
#endif
    }

    // determine if RSVP needed, not-needed, or response already recorded
    bool rsvpReq = rsvpRequested(inc);
    if (!rsvpReq && !firstAtt.isNull() && firstAtt.status() == Attendee::NeedsAction) {
        rsvpReq = true;
    }

    QString eventInfo;
    if (!myInc && !firstAtt.isNull()) {
        if (rsvpRec && inc) {
            if (incRevision == 0) {
#if KCALENDARCORE_VERSION < QT_VERSION_CHECK(6, 30, 0)
                eventInfo = i18n("Your <b>%1</b> response has been recorded.", KCalUtils::Stringify::attendeeStatus(eattendee.status()));
            } else {
                eventInfo = i18n("Your status for this invitation is <b>%1</b>.", KCalUtils::Stringify::attendeeStatus(eattendee.status()));
#else
                eventInfo = i18n("Your <b>%1</b> response has been recorded.", Attendee::statusName(eattendee.status()));
            } else {
                eventInfo = i18n("Your status for this invitation is <b>%1</b>.", Attendee::statusName(eattendee.status()));
#endif
            }
            rsvpReq = false;
        } else if (message->method() == iTIPCancel) {
            eventInfo = i18n("This invitation was canceled.");
        } else if (message->method() == iTIPAdd) {
            eventInfo = i18n("This invitation was accepted.");
        } else if (message->method() == iTIPDeclineCounter) {
            rsvpReq = true;
            eventInfo = rsvpRequestedStr(rsvpReq, role);
        } else {
            if (!isDelegated) {
                eventInfo = rsvpRequestedStr(rsvpReq, role);
            } else {
                eventInfo = i18n("Awaiting delegation response.");
            }
        }
    }
    incidence[QStringLiteral("eventInfo")] = eventInfo;

    // Print if the organizer gave you a preset status
    QString myStatus;
    if (!myInc) {
        if (inc && incRevision == 0) {
            myStatus = myStatusStr(inc);
        }
    }
    incidence[QStringLiteral("myStatus")] = myStatus;

    // Add groupware links
    QVariantList buttons;
    switch (message->method()) {
    case iTIPPublish:
    case iTIPRequest:
    case iTIPRefresh:
    case iTIPAdd:
        if (inc && incRevision > 0 && (existingIncidence || !helper->calendar())) {
            buttons += recordButtons(inc, helper);
        }

        if (!myInc) {
            if (!firstAtt.isNull()) {
                buttons += responseButtons(inc, rsvpReq, rsvpRec, helper);
            } else {
                buttons += responseButtons(inc, false, false, helper);
            }
        }
        break;

    case iTIPCancel:
        buttons = cancelButtons(inc, helper);
        break;

    case iTIPReply: {
        // Record invitation response
        Attendee a;
        Attendee ea;
        if (inc) {
            // Next, maybe this is a declined reply that was delegated from me?
            // find first attendee who is delegated-from me
            // look a their PARTSTAT response, if the response is declined,
            // then we need to start over which means putting all the action
            // buttons and NOT putting on the [Record response..] button
            a = findDelegatedFromMyAttendee(inc);
            if (!a.isNull()) {
                if (a.status() != Attendee::Accepted || a.status() != Attendee::Tentative) {
                    buttons = responseButtons(inc, rsvpReq, rsvpRec, helper);
                    break;
                }
            }

            // Finally, simply allow a Record of the reply
            if (!inc->attendees().isEmpty()) {
                a = inc->attendees().at(0);
            }
            if (!a.isNull() && helper->calendar()) {
                ea = findAttendee(existingIncidence, a.email());
            }
        }
        if (!ea.isNull() && (ea.status() != Attendee::NeedsAction) && (ea.status() == a.status())) {
#if KCALENDARCORE_VERSION < QT_VERSION_CHECK(6, 30, 0)
            const QString tStr = i18n("The <b>%1</b> response has been recorded", KCalUtils::Stringify::attendeeStatus(ea.status()));
#else
            const QString tStr = i18n("The <b>%1</b> response has been recorded", Attendee::statusName(ea.status()));
#endif
            buttons << inviteButton(QString(), tStr, QString(), helper);
        } else {
            if (inc) {
                buttons = recordResponseButtons(inc, helper);
            }
        }
        break;
    }

    case iTIPCounter:
        // Counter proposal
        buttons = counterButtons(helper);
        break;

    case iTIPDeclineCounter:
        buttons << responseButtons(inc, rsvpReq, rsvpRec, helper);
        break;

    case iTIPNoMethod:
        break;
    }

    incidence[QStringLiteral("buttons")] = buttons;

    // Add the attendee list
    if (inc->type() == Incidence::TypeTodo) {
        incidence[QStringLiteral("attendeesTitle")] = i18n("Assignees:");
    } else {
        incidence[QStringLiteral("attendeesTitle")] = i18n("Participants:");
    }
    if (myInc) {
        incidence[QStringLiteral("attendees")] = invitationRsvpList(existingIncidence, firstAtt);
    } else {
        incidence[QStringLiteral("attendees")] = invitationAttendeeList(inc);
    }

    // Add the attachment list
    incidence[QStringLiteral("attachments")] = invitationAttachments(inc, helper);

    const QStringList comments = inc->comments();
    if (!comments.isEmpty()) {
        incidence[QStringLiteral("comments")] = comments;
    }

    QString templateName;
    switch (inc->type()) {
    case KCalendarCore::IncidenceBase::TypeEvent:
        templateName = u"org.kde.messageviewer/calendar/itip_event.html"_s;
        break;
    case KCalendarCore::IncidenceBase::TypeTodo:
        templateName = u"org.kde.messageviewer/calendar/itip_todo.html"_s;
        break;
    case KCalendarCore::IncidenceBase::TypeJournal:
        templateName = u"org.kde.messageviewer/calendar/itip_journal.html"_s;
        break;
    case KCalendarCore::IncidenceBase::TypeFreeBusy:
        templateName = u"org.kde.messageviewer/calendar/itip_freebusy.html"_s;
        break;
    case KCalendarCore::IncidenceBase::TypeUnknown:
        return QString();
    }

    auto c = MessageViewer::MessagePartRendererManager::self()->createContext();
    c.insert(u"incidence"_s, incidence);
    auto t = MessageViewer::MessagePartRendererManager::self()->loadByName(templateName);
    const_cast<KTextTemplate::Engine *>(t->engine())->addDefaultLibrary(u"kitinerary_ktexttemplate_extension"_s);
    dynamic_cast<GrantleeTheme::Engine *>(const_cast<KTextTemplate::Engine *>(t->engine()))
        ->localizer()
        ->setApplicationDomain(QByteArrayLiteral("messageviewer_text_calendar_plugin"));
    auto result = t->render(&c);
    qobject_cast<GrantleeTheme::Engine *>(const_cast<KTextTemplate::Engine *>(t->engine()))
        ->localizer()
        ->setApplicationDomain(QByteArrayLiteral("libmessageviewer6"));
    return result;
}

//@endcond

static QString dateTimeToString(const QDateTime &date, bool allDay, bool shortfmt)
{
    if (allDay) {
        return QLocale().toString(date.toLocalTime().date(), shortfmt ? QLocale::ShortFormat : QLocale::LongFormat);
    }

    return QLocale().toString(date.toLocalTime(), (shortfmt ? QLocale::ShortFormat : QLocale::LongFormat));
}
