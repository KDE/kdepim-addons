/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimconfiguredialog.h"
#include "dkimconfigurewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

namespace
{
static const char myConfigGroupName[] = "DKIMConfigureDialog";
}

DKIMConfigureDialog::DKIMConfigureDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure DKIM"));
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mConfigureWidget = new DKIMConfigureWidget(this);
    mConfigureWidget->setObjectName(QStringLiteral("mConfigureWidget"));
    mainLayout->addWidget(mConfigureWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::RestoreDefaults, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &DKIMConfigureDialog::slotAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &DKIMConfigureDialog::reject);
    connect(buttonBox->button(QDialogButtonBox::RestoreDefaults), &QPushButton::clicked, this, &DKIMConfigureDialog::slotReset);
    mConfigureWidget->loadSettings();
    readConfig();
}

DKIMConfigureDialog::~DKIMConfigureDialog()
{
    writeConfig();
}

void DKIMConfigureDialog::slotAccepted()
{
    mConfigureWidget->saveSettings();
    accept();
}

void DKIMConfigureDialog::slotReset()
{
    mConfigureWidget->resetSettings();
}

void DKIMConfigureDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), myConfigGroupName);
    const QSize size = group.readEntry("Size", QSize(600, 400));
    if (size.isValid()) {
        resize(size);
    }
}

void DKIMConfigureDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), myConfigGroupName);
    group.writeEntry("Size", size());
    group.sync();
}
