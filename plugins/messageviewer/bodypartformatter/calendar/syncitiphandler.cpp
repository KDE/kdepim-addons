/*
  This file is part of kdepim.

  SPDX-FileCopyrightText: 2013 Sérgio Martins <iamsergio@gmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "syncitiphandler.h"
#include "text_calendar_debug.h"
#include <CalendarSupport/CalendarSingleton>

using namespace Akonadi;

SyncItipHandler::SyncItipHandler(const QString &receiver, const QString &iCal, const QString &type, const Akonadi::CalendarBase::Ptr &calendar, QObject *parent)
    : QObject(parent)
{
    Q_ASSERT(calendar);
    qCDebug(TEXT_CALENDAR_LOG) << "SyncItipHandler::SyncItipHandler: " << this;
    auto handler = new Akonadi::ITIPHandler(this);
    QObject::connect(handler, &Akonadi::ITIPHandler::iTipMessageProcessed, this, &SyncItipHandler::onITipMessageProcessed, Qt::QueuedConnection);

    handler->setCalendar(calendar);

    handler->processiTIPMessage(receiver, iCal, type);
}

SyncItipHandler::~SyncItipHandler()
{
    qCDebug(TEXT_CALENDAR_LOG) << "SyncItipHandler::~SyncItipHandler: " << this;
}

void SyncItipHandler::onITipMessageProcessed(Akonadi::ITIPHandler::Result result, const QString &errorMessage)
{
    m_result = result;
    m_errorMessage = errorMessage;
    deleteLater();
}

QString SyncItipHandler::errorMessage() const
{
    return m_errorMessage;
}

Akonadi::ITIPHandler::Result SyncItipHandler::result() const
{
    return m_result;
}

#include "moc_syncitiphandler.cpp"
