/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimconfigurewidget.h"
#include "dkimconfiguretab.h"

#include <MessageViewer/MessageViewerSettings>

#include <KConfigDialogManager>
#include <QVBoxLayout>

DKIMConfigureWidget::DKIMConfigureWidget(QWidget *parent)
    : QWidget(parent)
    , mTabWidget(new DKIMConfigureTab(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainLayout"));
    mainLayout->setContentsMargins({});

    mTabWidget->setObjectName(QLatin1StringView("tabwidget"));
    mainLayout->addWidget(mTabWidget);

    m_configDialogManager = new KConfigDialogManager(this, MessageViewer::MessageViewerSettings::self());
}

DKIMConfigureWidget::~DKIMConfigureWidget() = default;

void DKIMConfigureWidget::loadSettings()
{
    m_configDialogManager->updateWidgets();
    mTabWidget->loadSettings();
}

void DKIMConfigureWidget::saveSettings()
{
    m_configDialogManager->updateSettings();
    mTabWidget->saveSettings();
}

void DKIMConfigureWidget::resetSettings()
{
    m_configDialogManager->updateWidgetsDefault();
    mTabWidget->resetSettings();
}

#include "moc_dkimconfigurewidget.cpp"
