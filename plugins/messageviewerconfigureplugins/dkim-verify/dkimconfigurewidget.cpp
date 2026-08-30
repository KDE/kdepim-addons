/*
   SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimconfigurewidget.h"
#include "dkimconfiguretab.h"

#include <MessageViewer/MessageViewerSettings>

#include <KConfigDialogManager>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

DKIMConfigureWidget::DKIMConfigureWidget(QWidget *parent)
    : QWidget(parent)
    , mTabWidget(new DKIMConfigureTab(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    mTabWidget->setObjectName("tabwidget"_L1);
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
