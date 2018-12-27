/*
    Copyright (C) 2017-2019 Laurent Montel <montel@kde.org>

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

using namespace MailTransport;

SendMailConfigDialog::SendMailConfigDialog(MailTransport::Transport *transport, QWidget *parent)
    : QDialog(parent)
    , mTransport(transport)
    , mConfigWidget(nullptr)
    , mOkButton(nullptr)
{
    Q_ASSERT(transport);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mConfigWidget = new MailTransport::SendmailConfigWidget(transport, this);
    mConfigWidget->setObjectName(QStringLiteral("sendmailconfigwidget"));
    mainLayout->addWidget(mConfigWidget);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    mOkButton = buttonBox->button(QDialogButtonBox::Ok);
    mOkButton->setEnabled(false);
    mOkButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    mainLayout->addWidget(buttonBox);

    connect(mOkButton, &QAbstractButton::clicked, this, &SendMailConfigDialog::okClicked);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SendMailConfigDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SendMailConfigDialog::reject);
    connect(mConfigWidget, &MailTransport::SendmailConfigWidget::enableButtonOk, this, &SendMailConfigDialog::slotEnabledOkButton);
    slotEnabledOkButton(!mConfigWidget->pathIsEmpty());
}

SendMailConfigDialog::~SendMailConfigDialog()
{
}

void SendMailConfigDialog::slotEnabledOkButton(bool b)
{
    mOkButton->setEnabled(b);
}

void SendMailConfigDialog::okClicked()
{
    mConfigWidget->apply();
    mTransport->save();
}

void SendMailConfigDialog::slotTextChanged(const QString &text)
{
    mOkButton->setEnabled(!text.isEmpty());
}
