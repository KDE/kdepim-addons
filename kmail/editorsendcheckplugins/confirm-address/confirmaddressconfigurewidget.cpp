/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressconfigurewidget.h"
using namespace Qt::Literals::StringLiterals;

#include "confirmaddressconfiguretab.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <QCheckBox>
#include <QRegularExpression>
#include <QVBoxLayout>

ConfirmAddressConfigureWidget::ConfirmAddressConfigureWidget(QWidget *parent)
    : MessageComposer::PluginEditorConfigureBaseWidget(parent)
    , mConfirmAddressConfigureTab(new ConfirmAddressConfigureTab(this))
{
    auto vboxlayout = new QVBoxLayout(this);
    vboxlayout->setContentsMargins({});
    vboxlayout->setObjectName(QLatin1StringView("mainlayout"));
    mConfirmAddressConfigureTab->setObjectName(QLatin1StringView("confirmaddresstab"));
    connect(mConfirmAddressConfigureTab, &ConfirmAddressConfigureTab::configureChanged, this, &ConfirmAddressConfigureWidget::configureChanged);
    vboxlayout->addWidget(mConfirmAddressConfigureTab);
}

ConfirmAddressConfigureWidget::~ConfirmAddressConfigureWidget() = default;

void ConfirmAddressConfigureWidget::loadSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), u"Confirm Address"_s);
    mConfirmAddressConfigureTab->loadSettings(grp);
}

void ConfirmAddressConfigureWidget::saveSettings()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    // first, delete all filter groups:
    const QStringList filterGroups = config->groupList().filter(QRegularExpression(u"Confirm Address \\d+"_s));
    for (const QString &group : filterGroups) {
        config->deleteGroup(group);
    }
    KConfigGroup grp(config, u"Confirm Address"_s);
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

#include "moc_confirmaddressconfigurewidget.cpp"
