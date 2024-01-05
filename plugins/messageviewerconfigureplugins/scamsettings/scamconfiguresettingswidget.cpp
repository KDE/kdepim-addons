/*
   SPDX-FileCopyrightText: 2021-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "scamconfiguresettingswidget.h"
#include "scamconfiguresettingstreewidget.h"
#include <KLocalizedString>
#include <KSharedConfig>
#include <MessageViewer/ScamDetectionWhiteListSettingsManager>
#include <QHeaderView>
#include <QTreeWidget>
#include <QVBoxLayout>

ScamConfigureSettingsWidget::ScamConfigureSettingsWidget(QWidget *parent)
    : QWidget{parent}
    , mTreeWidget(new ScamConfigureSettingsTreeWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainLayout"));
    mainLayout->setContentsMargins({});

    mTreeWidget->setObjectName(QLatin1StringView("mTreeWidget"));
    mainLayout->addWidget(mTreeWidget);
    mTreeWidget->setRootIsDecorated(false);
    mTreeWidget->header()->setSectionsMovable(false);
    mTreeWidget->setHeaderLabels({i18n("Domain"), i18n("Check")});
}

ScamConfigureSettingsWidget::~ScamConfigureSettingsWidget() = default;

void ScamConfigureSettingsWidget::loadSettings()
{
    const QList<MessageViewer::ScamDetectionInfo> scanInfo = MessageViewer::ScamDetectionWhiteListSettingsManager::self()->scamDetectionInfoList();
    fillList(scanInfo);
}

void ScamConfigureSettingsWidget::saveSettings()
{
    QList<MessageViewer::ScamDetectionInfo> scanInfo;
    // TODO
    MessageViewer::ScamDetectionWhiteListSettingsManager::self()->setScamDetectionInfoList(scanInfo);
    // TODO
}

void ScamConfigureSettingsWidget::fillList(const QList<MessageViewer::ScamDetectionInfo> &scanInfo)
{
    // TODO
}

#include "moc_scamconfiguresettingswidget.cpp"
