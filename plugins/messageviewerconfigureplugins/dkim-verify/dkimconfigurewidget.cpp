/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimconfigurewidget.h"
#include "dkimconfiguretab.h"
#include <QVBoxLayout>

DKIMConfigureWidget::DKIMConfigureWidget(QWidget *parent)
    : QWidget(parent)
    , mTabWidget(new DKIMConfigureTab(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mTabWidget->setObjectName(QStringLiteral("tabwidget"));
    mainLayout->addWidget(mTabWidget);
}

DKIMConfigureWidget::~DKIMConfigureWidget() = default;

void DKIMConfigureWidget::loadSettings()
{
    mTabWidget->loadSettings();
}

void DKIMConfigureWidget::saveSettings()
{
    mTabWidget->saveSettings();
}

void DKIMConfigureWidget::resetSettings()
{
    mTabWidget->resetSettings();
}
