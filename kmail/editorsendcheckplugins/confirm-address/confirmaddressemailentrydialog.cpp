/*
   Copyright (C) 2017-2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
