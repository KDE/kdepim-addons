/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimkeyrecordwidget.h"
#include <MessageViewer/DKIMManagerKeyWidget>
#include <KConfigGroup>
#include <KSharedConfig>
#include <QHBoxLayout>

namespace {
static const char myConfigGroupName[] = "DKIMKeyRecordWidget";
}

DKIMKeyRecordWidget::DKIMKeyRecordWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mManagerKeyWidget = new MessageViewer::DKIMManagerKeyWidget(this);
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
    KConfigGroup group(KSharedConfig::openConfig(), myConfigGroupName);
    mManagerKeyWidget->restoreHeaders(group.readEntry("Header", QByteArray()));
}

void DKIMKeyRecordWidget::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), myConfigGroupName);
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
