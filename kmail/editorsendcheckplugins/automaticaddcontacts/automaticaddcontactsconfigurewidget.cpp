/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactsconfigurewidget.h"
#include "automaticaddcontactsconfiguretab.h"
#include <Akonadi/Collection>
#include <Akonadi/CollectionComboBox>
#include <KSharedConfig>
#include <QCheckBox>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

AutomaticAddContactsConfigureWidget::AutomaticAddContactsConfigureWidget(QWidget *parent)
    : MessageComposer::PluginEditorConfigureBaseWidget(parent)
    , mConfigureTab(new AutomaticAddContactsConfigureTab(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName("mainlayout"_L1);

    mConfigureTab->setObjectName("configuretab"_L1);
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
