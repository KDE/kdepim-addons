/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigurewidget.h"
#include <KLocalizedString>
#include <QHeaderView>
#include <QTreeWidget>
#include <QVBoxLayout>

OpenUrlWithConfigureWidget::OpenUrlWithConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mTreeWidget(new QTreeWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins());

    mTreeWidget->setObjectName(QStringLiteral("mTreeWidget"));
    mainLayout->addWidget(mTreeWidget);
    mTreeWidget->setRootIsDecorated(false);
    mTreeWidget->header()->setSectionsMovable(false);
    mTreeWidget->setHeaderLabels({i18n("Domain"), i18n("Command Line")});
}

OpenUrlWithConfigureWidget::~OpenUrlWithConfigureWidget()
{
}

void OpenUrlWithConfigureWidget::loadSettings()
{
    // TODO
}

void OpenUrlWithConfigureWidget::writeSettings()
{
    // TODO
}
