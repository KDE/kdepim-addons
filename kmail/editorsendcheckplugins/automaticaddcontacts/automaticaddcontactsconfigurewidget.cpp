/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactsconfigurewidget.h"
#include "automaticaddcontactsconfiguretab.h"
#include <Akonadi/Collection>
#include <Akonadi/CollectionComboBox>
#include <KSharedConfig>
#include <QCheckBox>
#include <QVBoxLayout>

AutomaticAddContactsConfigureWidget::AutomaticAddContactsConfigureWidget(QWidget *parent)
    : MessageComposer::PluginEditorConfigureBaseWidget(parent)
    , mConfigureTab(new AutomaticAddContactsConfigureTab(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));

    mConfigureTab->setObjectName(QLatin1StringView("configuretab"));
    mainLayout->addWidget(mConfigureTab);
    connect(mConfigureTab, &AutomaticAddContactsConfigureTab::configureChanged, this, &AutomaticAddContactsConfigureWidget::configureChanged);
}

AutomaticAddContactsConfigureWidget::~AutomaticAddContactsConfigureWidget() = default;

void AutomaticAddContactsConfigureWidget::loadSettings()
{
    mConfigureTab->loadSettings();
}

void AutomaticAddContactsConfigureWidget::saveSettings()
{
    mConfigureTab->saveSettings();
}

void AutomaticAddContactsConfigureWidget::resetSettings()
{
    mConfigureTab->resetSettings();
}

#include "moc_automaticaddcontactsconfigurewidget.cpp"
