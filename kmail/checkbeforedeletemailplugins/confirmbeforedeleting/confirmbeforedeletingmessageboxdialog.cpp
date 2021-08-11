/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingmessageboxdialog.h"
#include "confirmbeforedeletingmessageboxwidget.h"

#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>
ConfirmBeforeDeletingMessageBoxDialog::ConfirmBeforeDeletingMessageBoxDialog(QWidget *parent)
    : QDialog(parent)
    , mConfirmBeforeDeletingWidget(new ConfirmBeforeDeletingMessageBoxWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Confirm Delete Mail"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mConfirmBeforeDeletingWidget->setObjectName(QStringLiteral("mConfirmBeforeDeletingWidget"));
    mainLayout->addWidget(mConfirmBeforeDeletingWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Yes | QDialogButtonBox::Cancel | QDialogButtonBox::No, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ConfirmBeforeDeletingMessageBoxDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ConfirmBeforeDeletingMessageBoxDialog::reject);
}

ConfirmBeforeDeletingMessageBoxDialog::~ConfirmBeforeDeletingMessageBoxDialog()
{
}

void ConfirmBeforeDeletingMessageBoxDialog::setInfo(const QString &str)
{
    // TODO
}
