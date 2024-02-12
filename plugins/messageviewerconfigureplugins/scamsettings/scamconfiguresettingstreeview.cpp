/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "scamconfiguresettingstreeview.h"
#include <QHeaderView>
ScamConfigureSettingsTreeView::ScamConfigureSettingsTreeView(QWidget *parent)
    : QTreeView(parent)
{
    setContextMenuPolicy(Qt::DefaultContextMenu);
    for (int c = 0, total = header()->count(); c < total; ++c) {
        header()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
    setRootIsDecorated(false);
    setSortingEnabled(true);
}

ScamConfigureSettingsTreeView::~ScamConfigureSettingsTreeView() = default;

void ScamConfigureSettingsTreeView::contextMenuEvent(QContextMenuEvent *event)
{
    // TODO
}

#include "moc_scamconfiguresettingstreeview.cpp"
