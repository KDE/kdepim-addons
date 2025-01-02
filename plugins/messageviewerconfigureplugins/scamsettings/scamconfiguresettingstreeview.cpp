/*
   SPDX-FileCopyrightText: 2024-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "scamconfiguresettingstreeview.h"
#include "scamlistsmodel.h"
#include <KLocalizedString>
#include <QContextMenuEvent>
#include <QHeaderView>
#include <QMenu>

ScamConfigureSettingsTreeView::ScamConfigureSettingsTreeView(QWidget *parent)
    : QTreeView(parent)
    , mScamListsModel(new ScamListsModel(this))
{
    setContextMenuPolicy(Qt::DefaultContextMenu);
    for (int c = 0, total = header()->count(); c < total; ++c) {
        header()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
    setRootIsDecorated(false);
    setSortingEnabled(true);
    setModel(mScamListsModel);
}

ScamConfigureSettingsTreeView::~ScamConfigureSettingsTreeView() = default;

void ScamConfigureSettingsTreeView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;
    auto addAction = new QAction(QIcon::fromTheme(QStringLiteral("list-add")), i18n("Add…"), &menu);
    // TODO connect(addAction, &QAction::triggered, this, &AdblockFilterTreeView::slotAddAdblock);
    menu.addAction(addAction);

    menu.exec(event->globalPos());
}

#include "moc_scamconfiguresettingstreeview.cpp"
