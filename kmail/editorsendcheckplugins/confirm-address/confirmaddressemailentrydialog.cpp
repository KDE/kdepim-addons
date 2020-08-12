/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressemailentrydialog.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <PimCommon/EmailValidator>

ConfirmAddressEmailEntryDialog::ConfirmAddressEmailEntryDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    QLabel *label = new QLabel(i18n("Enter new domain name:"), this);
    label->setObjectName(QStringLiteral("label"));
    mainLayout->addWidget(label);

    mLineEdit = new QLineEdit(this);
    mLineEdit->setObjectName(QStringLiteral("lineedit"));
    mainLayout->addWidget(mLineEdit);

    PimCommon::EmailValidator *emailValidator = new PimCommon::EmailValidator(this);
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
