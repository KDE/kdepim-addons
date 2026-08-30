/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "confirmbeforedeletingdialog.h"
#include "confirmbeforedeletingwidget.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
using namespace Qt::Literals::StringLiterals;

namespace
{
const char myConfirmBeforeDeletingConfigGroupName[] = "ConfirmBeforeDeletingDialog";
}
ConfirmBeforeDeletingDialog::ConfirmBeforeDeletingDialog(QWidget *parent)
    : QDialog(parent)
    , mConfirmBeforeDeletingWidget(new ConfirmBeforeDeletingWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Before Deleting Mail"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainlayout"_L1);

    mConfirmBeforeDeletingWidget->setObjectName("mConfirmBeforeDeletingWidget"_L1);
    mainLayout->addWidget(mConfirmBeforeDeletingWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName("buttonBox"_L1);
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ConfirmBeforeDeletingDialog::slotSave);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ConfirmBeforeDeletingDialog::reject);
    readConfig();
}

ConfirmBeforeDeletingDialog::~ConfirmBeforeDeletingDialog()
{
    writeConfig();
}

void ConfirmBeforeDeletingDialog::slotSave()
{
    mConfirmBeforeDeletingWidget->save();
    accept();
}

void ConfirmBeforeDeletingDialog::writeConfig() const
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfirmBeforeDeletingConfigGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
    group.sync();
}

void ConfirmBeforeDeletingDialog::readConfig()
{
    create(); // ensure a window is created
    TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(this, QLatin1StringView(myConfirmBeforeDeletingConfigGroupName), 500, 300);
}

#include "moc_confirmbeforedeletingdialog.cpp"
