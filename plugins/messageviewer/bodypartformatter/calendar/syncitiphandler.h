/*
  This file is part of kdepim.

  SPDX-FileCopyrightText: 2013 Sérgio Martins <iamsergio@gmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SYNCITIPHANDLER_H
#define SYNCITIPHANDLER_H

#include <IncidenceEditor/GroupwareUiDelegate>
#include <Akonadi/Calendar/ITIPHandler>
#include <Akonadi/Calendar/CalendarBase>

#include <QObject>
#include <QEventLoop>

class SyncItipHandler : public QObject
{
    Q_OBJECT
public:
    SyncItipHandler(const QString &receiver, const QString &iCal, const QString &type, const Akonadi::CalendarBase::Ptr &calendar, QObject *parent = nullptr);
    ~SyncItipHandler();

public Q_SLOTS:
    void onITipMessageProcessed(Akonadi::ITIPHandler::Result, const QString &errorMessage);

public:
    QString errorMessage() const;
    Akonadi::ITIPHandler::Result result() const;

private:
    QString m_errorMessage;
    Akonadi::ITIPHandler::Result m_result = Akonadi::ITIPHandler::ResultSuccess;
    QEventLoop m_eventLoop;
    IncidenceEditorNG::GroupwareUiDelegate *m_counterProposalEditorDelegate = nullptr;
};

#endif // SYNCITIPHANDLER_H
