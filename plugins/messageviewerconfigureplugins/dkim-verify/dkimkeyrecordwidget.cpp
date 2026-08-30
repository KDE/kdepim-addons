/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimkeyrecordwidget.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <MessageViewer/DKIMManagerKeyWidget>
#include <QHBoxLayout>
using namespace Qt::Literals::StringLiterals;

namespace
{
const char myDKIMKeyRecordWidgetGroupName[] = "DKIMKeyRecordWidget";
}

DKIMKeyRecordWidget::DKIMKeyRecordWidget(QWidget *parent)
    : QWidget(parent)
    , mManagerKeyWidget(new MessageViewer::DKIMManagerKeyWidget(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);

    mManagerKeyWidget->setObjectName("mManagerKeyWidget"_L1);
    mainLayout->addWidget(mManagerKeyWidget);
}

DKIMKeyRecordWidget::~DKIMKeyRecordWidget()
{
    writeConfig();
}

void DKIMKeyRecordWidget::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myDKIMKeyRecordWidgetGroupName));
    mManagerKeyWidget->restoreHeaders(group.readEntry("Header", QByteArray()));
}

void DKIMKeyRecordWidget::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myDKIMKeyRecordWidgetGroupName));
    group.writeEntry("Header", mManagerKeyWidget->saveHeaders());
    group.sync();
}

void DKIMKeyRecordWidget::loadSettings()
{
    mManagerKeyWidget->loadKeys();
    readConfig();
}

void DKIMKeyRecordWidget::saveSettings()
{
    mManagerKeyWidget->saveKeys();
}

void DKIMKeyRecordWidget::resetSettings()
{
    mManagerKeyWidget->resetKeys();
}

#include "moc_dkimkeyrecordwidget.cpp"
