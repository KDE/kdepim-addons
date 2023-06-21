/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkbeforesendupdatesmtpdialog.h"
#include <KLocalizedString>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QVBoxLayout>

CheckBeforeSendUpdateSmtpDialog::CheckBeforeSendUpdateSmtpDialog(QWidget *parent)
    : QDialog(parent)
    , mChangeSmtp(new QCheckBox(i18n("Update SMTP server"), this))
{
    setWindowTitle(i18nc("@title:window", "Check SMTP server"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    auto lab = new QLabel(i18n("Do you want to send the email with a different SMTP than the one defined in the current identity?"), this);
    lab->setObjectName(QStringLiteral("label"));
    lab->setWordWrap(true);
    mainLayout->addWidget(lab);

    mChangeSmtp->setObjectName(QStringLiteral("changesmtp"));
    mChangeSmtp->setChecked(false);
    mainLayout->addWidget(mChangeSmtp);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Yes | QDialogButtonBox::No, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &CheckBeforeSendUpdateSmtpDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CheckBeforeSendUpdateSmtpDialog::reject);
}

CheckBeforeSendUpdateSmtpDialog::~CheckBeforeSendUpdateSmtpDialog() = default;

bool CheckBeforeSendUpdateSmtpDialog::changeSmtp() const
{
    return mChangeSmtp->isChecked();
}

#include "moc_checkbeforesendupdatesmtpdialog.cpp"
