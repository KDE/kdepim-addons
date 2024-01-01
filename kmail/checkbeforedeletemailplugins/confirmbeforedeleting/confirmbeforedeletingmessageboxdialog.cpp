/*
   SPDX-FileCopyrightText: 2021-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingmessageboxdialog.h"
#include "confirmbeforedeletingmessageboxwidget.h"

#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
ConfirmBeforeDeletingMessageBoxDialog::ConfirmBeforeDeletingMessageBoxDialog(QWidget *parent)
    : QDialog(parent)
    , mConfirmBeforeDeletingWidget(new ConfirmBeforeDeletingMessageBoxWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Confirm Delete Mail"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainLayout"));
    mConfirmBeforeDeletingWidget->setObjectName(QLatin1StringView("mConfirmBeforeDeletingWidget"));
    mainLayout->addWidget(mConfirmBeforeDeletingWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Yes | QDialogButtonBox::Cancel | QDialogButtonBox::No, this);
    buttonBox->setObjectName(QLatin1StringView("buttonBox"));
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::clicked, this, [this, buttonBox](QAbstractButton *button) {
        QDialogButtonBox::StandardButton code = buttonBox->standardButton(button);
        if (code != QDialogButtonBox::NoButton) {
            done(code);
        }
    });
}

ConfirmBeforeDeletingMessageBoxDialog::~ConfirmBeforeDeletingMessageBoxDialog() = default;

void ConfirmBeforeDeletingMessageBoxDialog::setInfo(const QString &str)
{
    mConfirmBeforeDeletingWidget->setInfo(str);
}

bool ConfirmBeforeDeletingMessageBoxDialog::useSameResult() const
{
    return mConfirmBeforeDeletingWidget->useSameResult();
}

#include "moc_confirmbeforedeletingmessageboxdialog.cpp"
