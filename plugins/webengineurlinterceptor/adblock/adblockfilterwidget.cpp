/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfilterwidget.h"
#include "adblockfilterlistsview.h"

#include <QLineEdit>
#include <QVBoxLayout>

AdblockFilterWidget::AdblockFilterWidget(QWidget *parent)
    : QWidget{parent}
    , mAdblockFilterListView(new AdblockFilterListsView(this))
    , mSearchLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mSearchLineEdit->setObjectName(QStringLiteral("mSearchLineEdit"));
    mainLayout->addWidget(mSearchLineEdit);

    mAdblockFilterListView->setObjectName(QStringLiteral("mAdblockFilterListView"));
    mainLayout->addWidget(mAdblockFilterListView);
}

AdblockFilterWidget::~AdblockFilterWidget() = default;

#include "moc_adblockfilterwidget.cpp"
