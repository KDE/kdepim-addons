/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactsconfiguretab.h"
#include "automaticaddcontactsconfigurewidget.h"
#include <AkonadiCore/Collection>
#include <AkonadiWidgets/CollectionComboBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <KSharedConfig>

AutomaticAddContactsConfigureWidget::AutomaticAddContactsConfigureWidget(QWidget *parent)
    : MessageComposer::PluginEditorCheckBeforeSendConfigureWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mConfigureTab = new AutomaticAddContactsConfigureTab(this);
    mConfigureTab->setObjectName(QStringLiteral("configuretab"));
    mainLayout->addWidget(mConfigureTab);
    connect(mConfigureTab, &AutomaticAddContactsConfigureTab::configureChanged, this, &AutomaticAddContactsConfigureWidget::configureChanged);
}

AutomaticAddContactsConfigureWidget::~AutomaticAddContactsConfigureWidget()
{
}

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
