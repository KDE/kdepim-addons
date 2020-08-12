/*
    SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
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
