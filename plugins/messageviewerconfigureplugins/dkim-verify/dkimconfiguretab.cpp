/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimconfiguretab.h"
#include "dkimadvancedwidget.h"
#include "dkimgeneralwidget.h"
#include "dkimkeyrecordwidget.h"
#include "dkimpolicywidget.h"
#include <KLocalizedString>
#include <KSharedConfig>
#include <QHBoxLayout>
#include <QTabWidget>

DKIMConfigureTab::DKIMConfigureTab(QWidget *parent)
    : QWidget(parent)
    , mGeneralWidget(new DKIMGeneralWidget(this))
    , mRecordWidget(new DKIMKeyRecordWidget(this))
    , mAdvancedWidget(new DKIMAdvancedWidget(this))
    , mPolicyWidget(new DKIMPolicyWidget(this))
    , mTabWidget(new QTabWidget(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    mTabWidget->setObjectName(QStringLiteral("tabwidget"));
    mainLayout->addWidget(mTabWidget);
    initTab();
}

DKIMConfigureTab::~DKIMConfigureTab() = default;

void DKIMConfigureTab::initTab()
{
    mTabWidget->addTab(mGeneralWidget, i18n("General"));

    mTabWidget->addTab(mRecordWidget, i18n("Record Keys"));

    mTabWidget->addTab(mPolicyWidget, i18n("Policy"));

    mTabWidget->addTab(mAdvancedWidget, i18n("Advanced"));
}

void DKIMConfigureTab::loadSettings()
{
    mGeneralWidget->loadSettings();
    mRecordWidget->loadSettings();
    mPolicyWidget->loadSettings();
    mAdvancedWidget->loadSettings();
}

void DKIMConfigureTab::saveSettings()
{
    mGeneralWidget->saveSettings();
    mRecordWidget->saveSettings();
    mPolicyWidget->saveSettings();
    mAdvancedWidget->saveSettings();
}

void DKIMConfigureTab::resetSettings()
{
    mGeneralWidget->resetSettings();
    mRecordWidget->resetSettings();
    mPolicyWidget->resetSettings();
    mAdvancedWidget->resetSettings();
}
