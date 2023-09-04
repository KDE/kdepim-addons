/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfilterwidget.h"
#include "adblockfilterlistsview.h"

#include <QVBoxLayout>

AdblockFilterWidget::AdblockFilterWidget(QWidget *parent)
    : QWidget{parent}
    , mAdblockFilterListView(new AdblockFilterListsView(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    // TODO add search line
    mAdblockFilterListView->setObjectName(QStringLiteral("mAdblockFilterListView"));
    mainLayout->addWidget(mAdblockFilterListView);
}

AdblockFilterWidget::~AdblockFilterWidget() = default;

#include "moc_adblockfilterwidget.cpp"
