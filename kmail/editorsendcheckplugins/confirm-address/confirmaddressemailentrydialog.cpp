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

ConfirmAddressEmailEntryDialog::ConfirmAddressEmailEntryDialog(QWidget *parent)
    : QDialog(parent)
    , mLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));
    auto label = new QLabel(i18nc("@label:textbox", "Enter new domain name:"), this);
    label->setObjectName(QLatin1StringView("label"));
    mainLayout->addWidget(label);

    mLineEdit->setObjectName(QLatin1StringView("lineedit"));
    mainLayout->addWidget(mLineEdit);

    auto emailValidator = new KEmailValidator(this);
    mLineEdit->setValidator(emailValidator);

    auto buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttons->setObjectName(QLatin1StringView("buttons"));
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
