/*
   SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimconfiguretab.h"
#include "dkimadvancedwidget.h"
#include "dkimgeneralwidget.h"
#include "dkimkeyrecordwidget.h"
#include "dkimpolicywidget.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QTabWidget>
using namespace Qt::Literals::StringLiterals;

DKIMConfigureTab::DKIMConfigureTab(QWidget *parent)
    : QWidget(parent)
    , mGeneralWidget(new DKIMGeneralWidget(this))
    , mRecordWidget(new DKIMKeyRecordWidget(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName("mainlayout"_L1);
    mainLayout->setContentsMargins({});

    auto tabWidget = new QTabWidget(this);
    tabWidget->setObjectName("tabwidget"_L1);
    mainLayout->addWidget(tabWidget);

    tabWidget->addTab(mGeneralWidget, i18n("General"));
    tabWidget->addTab(mRecordWidget, i18n("Record Keys"));
    tabWidget->addTab(new DKIMPolicyWidget(this), i18n("Policy"));
    tabWidget->addTab(new DKIMAdvancedWidget(this), i18n("Advanced"));
}

DKIMConfigureTab::~DKIMConfigureTab() = default;

void DKIMConfigureTab::loadSettings()
{
    mRecordWidget->loadSettings();
}

void DKIMConfigureTab::saveSettings()
{
    mGeneralWidget->saveSettings();
    mRecordWidget->saveSettings();
}

void DKIMConfigureTab::resetSettings()
{
    mRecordWidget->resetSettings();
}

#include "moc_dkimconfiguretab.cpp"
