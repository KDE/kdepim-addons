/*
   Copyright (C) 2018-2019 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "dkimadvancedwidget.h"
#include "dkimconfiguretab.h"
#include "dkimgeneralwidget.h"
#include "dkimkeyrecordwidget.h"
#include "dkimpolicywidget.h"
#include <KSharedConfig>
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QRegularExpression>
#include <QTabWidget>

DKIMConfigureTab::DKIMConfigureTab(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mTabWidget = new QTabWidget(this);
    mTabWidget->setObjectName(QStringLiteral("tabwidget"));
    mainLayout->addWidget(mTabWidget);
    initTab();
}

DKIMConfigureTab::~DKIMConfigureTab()
{
}

void DKIMConfigureTab::initTab()
{
    mGeneralWidget = new DKIMGeneralWidget(this);
    mTabWidget->addTab(mGeneralWidget, i18n("General"));

    mRecordWidget = new DKIMKeyRecordWidget(this);
    mTabWidget->addTab(mRecordWidget, i18n("Record Keys"));

    mPolicyWidget = new DKIMPolicyWidget(this);
    mTabWidget->addTab(mPolicyWidget, i18n("Policy"));

    mAdvancedWidget = new DKIMAdvancedWidget(this);
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
