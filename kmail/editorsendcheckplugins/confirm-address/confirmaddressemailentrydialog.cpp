/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressemailentrydialog.h"
#include <KLocalizedString>
#include <PimCommon/EmailValidator>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

ConfirmAddressEmailEntryDialog::ConfirmAddressEmailEntryDialog(QWidget *parent)
    : QDialog(parent)
    , mLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    QLabel *label = new QLabel(i18n("Enter new domain name:"), this);
    label->setObjectName(QStringLiteral("label"));
    mainLayout->addWidget(label);

    mLineEdit->setObjectName(QStringLiteral("lineedit"));
    mainLayout->addWidget(mLineEdit);

    auto emailValidator = new PimCommon::EmailValidator(this);
    mLineEdit->setValidator(emailValidator);

    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttons->setObjectName(QStringLiteral("buttons"));
    mainLayout->addWidget(buttons);
    connect(buttons, &QDialogButtonBox::accepted, this, &ConfirmAddressEmailEntryDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &ConfirmAddressEmailEntryDialog::reject);
}

QString ConfirmAddressEmailEntryDialog::emails() const
{
    return mLineEdit->text();
}

void ConfirmAddressEmailEntryDialog::setValue(const QString &val)
{
    mLineEdit->setText(val);
}
