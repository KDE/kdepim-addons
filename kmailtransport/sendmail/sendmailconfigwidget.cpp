/*
  Copyright (c) 2013 Laurent Montel <montel@kde.org>
  Copyright (c) 2009 Constantin Berzan <exit3219@gmail.com>

  Based on MailTransport code by:
  Copyright (c) 2006 - 2007 Volker Krause <vkrause@kde.org>
  Copyright (c) 2007 KovoKs <kovoks@kovoks.nl>

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

#include "sendmailconfigwidget.h"
#include "mailtransport/private/transportconfigwidget_p.h"
#include "ui_sendmailsettings.h"

#include <QStandardPaths>
#include <KLineEdit>

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
    d->ui.kcfg_host->setMode(KFile::File|KFile::ExistingOnly|KFile::LocalOnly);
    d->ui.kcfg_host->setFocus();
    d->manager->addWidget(this); // otherwise it doesn't find out about these widgets
    d->manager->updateWidgets();

    if (d->ui.kcfg_host->url().isEmpty()) {
        // Locate sendmail.
        // This is imperfect, because it shows the standard path if an empty path
        // is saved in the config.
        d->ui.kcfg_host->setText(QStandardPaths::findExecutable(QStringLiteral("sendmail")));
    }
    connect(d->ui.kcfg_host->lineEdit(), SIGNAL(textChanged(QString)),
            SLOT(slotTextChanged(QString)));
    slotTextChanged(d->ui.kcfg_host->text());
}

void SendmailConfigWidget::slotTextChanged(const QString &text)
{
    Q_EMIT enableButtonOk(!text.isEmpty());
}

bool SendmailConfigWidget::pathIsEmpty() const
{
    Q_D(const SendmailConfigWidget);
    return d->ui.kcfg_host->text().isEmpty();
}
