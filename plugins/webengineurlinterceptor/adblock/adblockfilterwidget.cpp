/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfilterwidget.h"
#include "adblockfiltertreeview.h"

#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QLineEdit>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

AdblockFilterWidget::AdblockFilterWidget(QWidget *parent)
    : QWidget{parent}
    , mAdblockFilterListView(new AdblockFilterTreeView(this))
    , mSearchLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    mSearchLineEdit->setObjectName("mSearchLineEdit"_L1);
    mainLayout->addWidget(mSearchLineEdit);
    mSearchLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Search…"));
    mSearchLineEdit->setClearButtonEnabled(true);
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);

    mAdblockFilterListView->setObjectName("mAdblockFilterListView"_L1);
    mainLayout->addWidget(mAdblockFilterListView);
    connect(mSearchLineEdit, &QLineEdit::textChanged, mAdblockFilterListView, &AdblockFilterTreeView::setFilterString);
    connect(mAdblockFilterListView, &AdblockFilterTreeView::settingsChanged, this, &AdblockFilterWidget::settingsChanged);
}

AdblockFilterWidget::~AdblockFilterWidget() = default;

void AdblockFilterWidget::loadSettings()
{
    mAdblockFilterListView->loadSettings();
}

void AdblockFilterWidget::saveSettings()
{
    mAdblockFilterListView->saveSettings();
}

#include "moc_adblockfilterwidget.cpp"
