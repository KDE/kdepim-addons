/*
   Copyright (C) 2017-2019 Montel Laurent <montel@kde.org>

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

#include "checkbeforesendupdatesmtpdialog.h"
#include <KLocalizedString>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QCheckBox>

CheckBeforeSendUpdateSmtpDialog::CheckBeforeSendUpdateSmtpDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18n("Check SMTP server"));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    QLabel *lab = new QLabel(i18n("Do you want to send the email with a different SMTP than the one defined in the current identity?"), this);
    lab->setObjectName(QStringLiteral("label"));
    lab->setWordWrap(true);
    mainLayout->addWidget(lab);

    mChangeSmtp = new QCheckBox(i18n("Update SMTP server"), this);
    mChangeSmtp->setObjectName(QStringLiteral("changesmtp"));
    mChangeSmtp->setChecked(false);
    mainLayout->addWidget(mChangeSmtp);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Yes | QDialogButtonBox::No, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &CheckBeforeSendUpdateSmtpDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CheckBeforeSendUpdateSmtpDialog::reject);
}

CheckBeforeSendUpdateSmtpDialog::~CheckBeforeSendUpdateSmtpDialog()
{
}

bool CheckBeforeSendUpdateSmtpDialog::changeSmtp() const
{
    return mChangeSmtp->isChecked();
}
