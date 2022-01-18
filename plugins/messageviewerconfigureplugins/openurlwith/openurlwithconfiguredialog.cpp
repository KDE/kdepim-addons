/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfiguredialog.h"
#include "openurlwithconfigurewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>

namespace
{
static const char myOpenUrlWithConfigureConfigGroupName[] = "OpenUrlWithConfigureDialog";
}

OpenUrlWithConfigureDialog::OpenUrlWithConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mOpenUrlWithWidget(new OpenUrlWithConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Open Url With Plugin"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mOpenUrlWithWidget->setObjectName(QStringLiteral("mOpenUrlWithWidget"));
    mainLayout->addWidget(mOpenUrlWithWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
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
    KConfigGroup grp(KSharedConfig::openStateConfig(), myOpenUrlWithConfigureConfigGroupName);
    const QSize size = grp.readEntry("Size", QSize(300, 200));
    if (size.isValid()) {
        resize(size);
    }
}

void OpenUrlWithConfigureDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), myOpenUrlWithConfigureConfigGroupName);
    grp.writeEntry("Size", size());
    grp.sync();
}
