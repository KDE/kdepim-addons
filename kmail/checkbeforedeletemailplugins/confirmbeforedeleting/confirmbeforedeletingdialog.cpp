/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "confirmbeforedeletingdialog.h"
#include "confirmbeforedeletingwidget.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>

namespace
{
static const char myConfirmBeforeDeletingConfigGroupName[] = "ConfirmBeforeDeletingDialog";
}
ConfirmBeforeDeletingDialog::ConfirmBeforeDeletingDialog(QWidget *parent)
    : QDialog(parent)
    , mConfirmBeforeDeletingWidget(new ConfirmBeforeDeletingWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Before Deleting Mail"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mConfirmBeforeDeletingWidget->setObjectName(QStringLiteral("mConfirmBeforeDeletingWidget"));
    mainLayout->addWidget(mConfirmBeforeDeletingWidget);

    auto box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    box->setObjectName(QStringLiteral("box"));
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &ConfirmBeforeDeletingDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &ConfirmBeforeDeletingDialog::reject);
    readConfig();
}

ConfirmBeforeDeletingDialog::~ConfirmBeforeDeletingDialog()
{
    writeConfig();
}

void ConfirmBeforeDeletingDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfirmBeforeDeletingConfigGroupName);
    group.writeEntry("Size", size());
}

void ConfirmBeforeDeletingDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfirmBeforeDeletingConfigGroupName);
    const QSize sizeDialog = group.readEntry("Size", QSize(500, 300));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}
