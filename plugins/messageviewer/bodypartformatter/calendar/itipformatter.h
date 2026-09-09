/*
  SPDX-FileCopyrightText: 2001-2003 Cornelius Schumacher <schumacher@kde.org>
  SPDX-FileCopyrightText: 2004 Reinhold Kainhofer <reinhold@kainhofer.com>
  SPDX-FileCopyrightText: 2009-2010 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <KCalendarCore/Calendar>
#include <KCalendarCore/Incidence>
#include <KCalendarCore/ScheduleMessage>

#include <QDate>

#include <memory>

class InvitationFormatterHelperPrivate;

/*!
 * \class InvitationFormatterHelper
 *
 * \brief The InvitationFormatterHelper class
 */
class InvitationFormatterHelper
{
public:
    /*!
      Constructor of the InvitationFormatterHelper class.
     */
    InvitationFormatterHelper();
    /*!
      Destructor of the InvitationFormatterHelper class.
     */
    virtual ~InvitationFormatterHelper();
    /*!
      Generate a URL link for the specified ID.
      \param id the identifier for which to generate the link
      \return the generated link URL
     */
    [[nodiscard]] virtual QString generateLinkURL(const QString &id);
    /*!
      Make a formatted link with the specified ID and text.
      \param id the identifier for the link
      \param text the text to display for the link
      \return the formatted link
     */
    [[nodiscard]] virtual QString makeLink(const QString &id, const QString &text);
    /*!
      Get the calendar associated with this formatter helper.
      \return a pointer to the calendar
     */
    [[nodiscard]] virtual KCalendarCore::Calendar::Ptr calendar() const;

private:
    Q_DISABLE_COPY(InvitationFormatterHelper)
    std::unique_ptr<InvitationFormatterHelperPrivate> const d;
};

/*!
 \class ItipFormatter

  \brief
  Provides methods to format Incidences in various ways for display purposes.

  Helpers that provides several static methods to format an Incidence in
  different ways: like an HTML representation for KMail, a representation
  for tool tips, or a representation for a viewer widget.

*/
namespace ItipFormatter
{
/*!
  Deliver an HTML formatted string displaying an invitation.

  \param message an iCal schedule message ("invitation")
  \param helper a pointer to an InvitationFormatterHelper.
  \param sender a QString containing the email address of the person sending the invitation.
  \return the formatted HTML invitation string

  \since 6.9
*/
QString formatICalInvitation(const KCalendarCore::ScheduleMessage::Ptr &message, InvitationFormatterHelper *helper, const QString &sender);

template<typename T>
class ScheduleMessageVisitor;
class InvitationHeaderVisitor;
class InvitationBodyVisitor;
}
