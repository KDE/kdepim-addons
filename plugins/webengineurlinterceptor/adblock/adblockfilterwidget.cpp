/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfilterwidget.h"
#include "adblockfiltertreeview.h"

#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QLineEdit>
#include <QVBoxLayout>

AdblockFilterWidget::AdblockFilterWidget(QWidget *parent)
    : QWidget{parent}
    , mAdblockFilterListView(new AdblockFilterTreeView(this))
    , mSearchLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainLayout"));
    mainLayout->setContentsMargins({});

    mSearchLineEdit->setObjectName(QLatin1StringView("mSearchLineEdit"));
    mainLayout->addWidget(mSearchLineEdit);
    mSearchLineEdit->setPlaceholderText(i18n("Search..."));
    mSearchLineEdit->setClearButtonEnabled(true);
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);

    mAdblockFilterListView->setObjectName(QLatin1StringView("mAdblockFilterListView"));
    mainLayout->addWidget(mAdblockFilterListView);
    connect(mSearchLineEdit, &QLineEdit::textChanged, mAdblockFilterListView, &AdblockFilterTreeView::setFilterString);
    connect(mAdblockFilterListView, &AdblockFilterTreeView::settingsChanged, this, &AdblockFilterWidget::settingsChanged);
}

AdblockFilterWidget::~AdblockFilterWidget() = default;

void AdblockFilterWidget::loadSettings()
{
    mAdblockFilterListView->loadSettings();
}

void AdblockFilterWidget::saveSettings() const
{
    mAdblockFilterListView->saveSettings();
}

#include "moc_adblockfilterwidget.cpp"
