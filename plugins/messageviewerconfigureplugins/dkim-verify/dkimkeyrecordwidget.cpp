/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimkeyrecordwidget.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <MessageViewer/DKIMManagerKeyWidget>
#include <QHBoxLayout>

namespace
{
static const char myDKIMKeyRecordWidgetGroupName[] = "DKIMKeyRecordWidget";
}

DKIMKeyRecordWidget::DKIMKeyRecordWidget(QWidget *parent)
    : QWidget(parent)
    , mManagerKeyWidget(new MessageViewer::DKIMManagerKeyWidget(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mManagerKeyWidget->setObjectName(QStringLiteral("mManagerKeyWidget"));
    mainLayout->addWidget(mManagerKeyWidget);
    readConfig();
}

DKIMKeyRecordWidget::~DKIMKeyRecordWidget()
{
    writeConfig();
}

void DKIMKeyRecordWidget::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), myDKIMKeyRecordWidgetGroupName);
    mManagerKeyWidget->restoreHeaders(group.readEntry("Header", QByteArray()));
}

void DKIMKeyRecordWidget::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), myDKIMKeyRecordWidgetGroupName);
    group.writeEntry("Header", mManagerKeyWidget->saveHeaders());
    group.sync();
}

void DKIMKeyRecordWidget::loadSettings()
{
    mManagerKeyWidget->loadKeys();
}

void DKIMKeyRecordWidget::saveSettings()
{
    mManagerKeyWidget->saveKeys();
}

void DKIMKeyRecordWidget::resetSettings()
{
    mManagerKeyWidget->resetKeys();
}
