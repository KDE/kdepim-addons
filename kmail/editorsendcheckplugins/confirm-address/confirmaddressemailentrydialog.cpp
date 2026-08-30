/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressemailentrydialog.h"
#include <KEmailValidator>
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

ConfirmAddressEmailEntryDialog::ConfirmAddressEmailEntryDialog(QWidget *parent)
    : QDialog(parent)
    , mLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainlayout"_L1);
    auto label = new QLabel(i18nc("@label:textbox", "Enter new domain name:"), this);
    label->setObjectName("label"_L1);
    mainLayout->addWidget(label);

    mLineEdit->setObjectName("lineedit"_L1);
    mainLayout->addWidget(mLineEdit);

    auto emailValidator = new KEmailValidator(this);
    mLineEdit->setValidator(emailValidator);

    auto buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttons->setObjectName("buttons"_L1);
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

#include "moc_confirmaddressemailentrydialog.cpp"
