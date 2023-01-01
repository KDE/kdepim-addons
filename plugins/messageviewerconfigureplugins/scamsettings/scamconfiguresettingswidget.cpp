/*
   SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "scamconfiguresettingswidget.h"
#include <KLocalizedString>
#include <KSharedConfig>
#include <QHeaderView>
#include <QTreeWidget>
#include <QVBoxLayout>

ScamConfigureSettingsWidget::ScamConfigureSettingsWidget(QWidget *parent)
    : QWidget{parent}
    , mTreeWidget(new QTreeWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mTreeWidget->setObjectName(QStringLiteral("mTreeWidget"));
    mainLayout->addWidget(mTreeWidget);
    mTreeWidget->setRootIsDecorated(false);
    mTreeWidget->header()->setSectionsMovable(false);
    mTreeWidget->setHeaderLabels({i18n("Domain"), i18n("Check")});
}

ScamConfigureSettingsWidget::~ScamConfigureSettingsWidget() = default;

void ScamConfigureSettingsWidget::loadSettings()
{
    // TODO
}

void ScamConfigureSettingsWidget::saveSettings()
{
    // TODO
}
