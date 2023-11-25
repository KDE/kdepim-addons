/*
   SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

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
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));

    mConfirmBeforeDeletingWidget->setObjectName(QLatin1StringView("mConfirmBeforeDeletingWidget"));
    mainLayout->addWidget(mConfirmBeforeDeletingWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QLatin1StringView("buttonBox"));
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

void ConfirmBeforeDeletingDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1String(myConfirmBeforeDeletingConfigGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
    group.sync();
}

void ConfirmBeforeDeletingDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(500, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1String(myConfirmBeforeDeletingConfigGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

#include "moc_confirmbeforedeletingdialog.cpp"
