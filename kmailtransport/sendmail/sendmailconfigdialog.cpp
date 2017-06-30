/*
    Copyright (c) 2017 Laurent Montel <montel@kde.org>

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

#include "sendmailconfigdialog.h"
#include "sendmailconfigwidget.h"

#include "transport.h"

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

using namespace MailTransport;

class MailTransport::SendMailConfigDialog::Private
{
public:
    Private(SendMailConfigDialog *qq)
        : transport(nullptr)
        , configWidget(nullptr)
        , q(qq)
        , okButton(nullptr)
    {
    }

    Transport *transport;
    SendmailConfigWidget *configWidget;
    SendMailConfigDialog *q;
    QPushButton *okButton;

    void okClicked();
    void slotTextChanged(const QString &text);
    void slotEnabledOkButton(bool);
};

void SendMailConfigDialog::Private::slotEnabledOkButton(bool b)
{
    okButton->setEnabled(b);
}

void SendMailConfigDialog::Private::okClicked()
{
    configWidget->apply();
    transport->save();
}

void SendMailConfigDialog::Private::slotTextChanged(const QString &text)
{
    okButton->setEnabled(!text.isEmpty());
}

SendMailConfigDialog::SendMailConfigDialog(Transport *transport, QWidget *parent)
    : QDialog(parent)
    , d(new Private(this))
{
    Q_ASSERT(transport);
    d->transport = transport;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    d->configWidget = new MailTransport::SendmailConfigWidget(transport, this);
    mainLayout->addWidget(d->configWidget);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    d->okButton = buttonBox->button(QDialogButtonBox::Ok);
    d->okButton->setEnabled(false);
    d->okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    mainLayout->addWidget(buttonBox);

    connect(d->okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SendMailConfigDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SendMailConfigDialog::reject);
    connect(d->configWidget, SIGNAL(enableButtonOk(bool)), this, SLOT(slotEnabledOkButton(bool)));
}

SendMailConfigDialog::~SendMailConfigDialog()
{
    delete d;
}

#include "moc_sendmailconfigdialog.cpp"
