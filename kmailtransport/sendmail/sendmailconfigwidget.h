/*
  SPDX-FileCopyrightText: 2009 Constantin Berzan <exit3219@gmail.com>

  Based on MailTransport code by:
  SPDX-FileCopyrightText: 2006-2007 Volker Krause <vkrause@kde.org>

  Based on KMail code by:
  SPDX-FileCopyrightText: 2001-2002 Michael Haeckel <haeckel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <MailTransport/TransportConfigWidget>

namespace MailTransport
{
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
    [[nodiscard]] bool pathIsEmpty() const;
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
