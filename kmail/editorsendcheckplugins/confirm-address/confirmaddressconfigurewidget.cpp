/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressconfiguretab.h"
#include "confirmaddressconfigurewidget.h"
#include <QCheckBox>
#include <QVBoxLayout>
#include <KConfigGroup>
#include <KSharedConfig>
#include <QRegularExpression>

ConfirmAddressConfigureWidget::ConfirmAddressConfigureWidget(QWidget *parent)
    : MessageComposer::PluginEditorCheckBeforeSendConfigureWidget(parent)
{
    auto *vboxlayout = new QVBoxLayout(this);
    vboxlayout->setContentsMargins({});
    vboxlayout->setObjectName(QStringLiteral("mainlayout"));
    mConfirmAddressConfigureTab = new ConfirmAddressConfigureTab(this);
    mConfirmAddressConfigureTab->setObjectName(QStringLiteral("confirmaddresstab"));
    connect(mConfirmAddressConfigureTab, &ConfirmAddressConfigureTab::configureChanged, this, &ConfirmAddressConfigureWidget::configureChanged);
    vboxlayout->addWidget(mConfirmAddressConfigureTab);
}

ConfirmAddressConfigureWidget::~ConfirmAddressConfigureWidget()
{
}

void ConfirmAddressConfigureWidget::loadSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Confirm Address");
    mConfirmAddressConfigureTab->loadSettings(grp);
}

void ConfirmAddressConfigureWidget::saveSettings()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    // first, delete all filter groups:
    const QStringList filterGroups = config->groupList().filter(QRegularExpression(QStringLiteral("Confirm Address \\d+")));
    for (const QString &group : filterGroups) {
        config->deleteGroup(group);
    }
    KConfigGroup grp(config, "Confirm Address");
    mConfirmAddressConfigureTab->saveSettings(grp);
}

void ConfirmAddressConfigureWidget::resetSettings()
{
    mConfirmAddressConfigureTab->resetSettings();
}

void ConfirmAddressConfigureWidget::slotEnableChanged(bool state)
{
    Q_UNUSED(state)
    Q_EMIT configureChanged();
}
