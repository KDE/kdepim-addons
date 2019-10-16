/*
  Copyright (c) 2009 Constantin Berzan <exit3219@gmail.com>

  Based on MailTransport code by:
  Copyright (c) 2006 - 2007 Volker Krause <vkrause@kde.org>

  Based on KMail code by:
  Copyright (c) 2001-2002 Michael Haeckel <haeckel@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.
*/

#ifndef MAILTRANSPORT_SENDMAILCONFIGWIDGET_H
#define MAILTRANSPORT_SENDMAILCONFIGWIDGET_H

#include "transportconfigwidget.h"

namespace MailTransport {
class Transport;

/**
  @internal
*/
class SendmailConfigWidgetPrivate;

/**
  @internal
  Configuration widget for a Sendmail transport.
*/
class SendmailConfigWidget : public TransportConfigWidget
{
    Q_OBJECT

public:
    explicit SendmailConfigWidget(Transport *transport, QWidget *parent = nullptr);
    Q_REQUIRED_RESULT bool pathIsEmpty() const;
Q_SIGNALS:
    void enableButtonOk(bool);

public Q_SLOTS:
    void apply() override;

private Q_SLOTS:
    void slotTextChanged(const QString &text);

protected:
    SendmailConfigWidget(SendmailConfigWidgetPrivate &dd, Transport *transport, QWidget *parent);

private:
    Q_DECLARE_PRIVATE(SendmailConfigWidget)

    void init();
};
} // namespace MailTransport

#endif // MAILTRANSPORT_SENDMAILCONFIGWIDGET_H
