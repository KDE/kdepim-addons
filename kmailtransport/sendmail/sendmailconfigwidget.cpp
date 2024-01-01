/*
  SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2009 Constantin Berzan <exit3219@gmail.com>

  Based on MailTransport code by:
  SPDX-FileCopyrightText: 2006-2007 Volker Krause <vkrause@kde.org>
  SPDX-FileCopyrightText: 2007 KovoKs <kovoks@kovoks.nl>

  Based on KMail code by:
  SPDX-FileCopyrightText: 2001-2002 Michael Haeckel <haeckel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "sendmailconfigwidget.h"
#include "mailtransport/private/transportconfigwidget_p.h"
#include "ui_sendmailsettings.h"

#include <KLineEdit>
#include <QStandardPaths>

using namespace MailTransport;

class MailTransport::SendmailConfigWidgetPrivate : public TransportConfigWidgetPrivate
{
public:
    ::Ui::SendmailSettings ui;
};

SendmailConfigWidget::SendmailConfigWidget(Transport *transport, QWidget *parent)
    : TransportConfigWidget(*new SendmailConfigWidgetPrivate, transport, parent)
{
    init();
}

SendmailConfigWidget::SendmailConfigWidget(SendmailConfigWidgetPrivate &dd, Transport *transport, QWidget *parent)
    : TransportConfigWidget(dd, transport, parent)
{
    init();
}

void SendmailConfigWidget::init()
{
    Q_D(SendmailConfigWidget);

    d->ui.setupUi(this);
    d->ui.kcfg_host->setMode(KFile::File | KFile::ExistingOnly | KFile::LocalOnly);
    d->ui.kcfg_host->setFocus();
    d->manager->addWidget(this); // otherwise it doesn't find out about these widgets
    d->manager->updateWidgets();

    if (d->ui.kcfg_host->url().isEmpty()) {
        // Locate sendmail.
        // This is imperfect, because it shows the standard path if an empty path
        // is saved in the config.
        d->ui.kcfg_host->setText(QStandardPaths::findExecutable(QStringLiteral("sendmail")));
    }
    connect(d->ui.kcfg_host->lineEdit(), &QLineEdit::textChanged, this, &SendmailConfigWidget::slotTextChanged);
    slotTextChanged(d->ui.kcfg_host->text());
}

void SendmailConfigWidget::slotTextChanged(const QString &text)
{
    Q_EMIT enableButtonOk(!text.trimmed().isEmpty());
}

bool SendmailConfigWidget::pathIsEmpty() const
{
    Q_D(const SendmailConfigWidget);
    return d->ui.kcfg_host->text().trimmed().isEmpty();
}

void SendmailConfigWidget::apply()
{
    Q_D(const SendmailConfigWidget);
    d->ui.kcfg_options->setText(d->ui.kcfg_options->text().trimmed());
    TransportConfigWidget::apply();
}

#include "moc_sendmailconfigwidget.cpp"
