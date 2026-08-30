/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkbeforesendupdatesmtpdialog.h"
#include <KLocalizedString>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

CheckBeforeSendUpdateSmtpDialog::CheckBeforeSendUpdateSmtpDialog(QWidget *parent)
    : QDialog(parent)
    , mChangeSmtp(new QCheckBox(i18nc("@option:check", "Update SMTP server"), this))
{
    setWindowTitle(i18nc("@title:window", "Check SMTP server"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainlayout"_L1);

    auto lab = new QLabel(i18nc("@label:textbox", "Do you want to send the email with a different SMTP than the one defined in the current identity?"), this);
    lab->setObjectName("label"_L1);
    lab->setWordWrap(true);
    mainLayout->addWidget(lab);

    mChangeSmtp->setObjectName("changesmtp"_L1);
    mChangeSmtp->setChecked(false);
    mainLayout->addWidget(mChangeSmtp);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Yes | QDialogButtonBox::No, this);
    buttonBox->setObjectName("buttonbox"_L1);
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
