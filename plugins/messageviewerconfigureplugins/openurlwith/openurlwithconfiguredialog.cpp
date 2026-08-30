/*
   SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfiguredialog.h"
#include "openurlwithconfigurewidget.h"
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
const char myOpenUrlWithConfigureConfigGroupName[] = "OpenUrlWithConfigureDialog";
}

OpenUrlWithConfigureDialog::OpenUrlWithConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mOpenUrlWithWidget(new OpenUrlWithConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Open Url With Plugin"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainlayout"_L1);

    mOpenUrlWithWidget->setObjectName("mOpenUrlWithWidget"_L1);
    mainLayout->addWidget(mOpenUrlWithWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName("buttonBox"_L1);
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &OpenUrlWithConfigureDialog::slotAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &OpenUrlWithConfigureDialog::reject);
    mOpenUrlWithWidget->loadSettings();
    readConfig();
}

OpenUrlWithConfigureDialog::~OpenUrlWithConfigureDialog()
{
    writeConfig();
}

void OpenUrlWithConfigureDialog::slotAccepted()
{
    mOpenUrlWithWidget->writeSettings();
    accept();
}

void OpenUrlWithConfigureDialog::readConfig()
{
    create(); // ensure a window is created
    TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(this, QLatin1StringView(myOpenUrlWithConfigureConfigGroupName), 300, 200);
}

void OpenUrlWithConfigureDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), QLatin1StringView(myOpenUrlWithConfigureConfigGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), grp);
    grp.sync();
}

#include "moc_openurlwithconfiguredialog.cpp"
