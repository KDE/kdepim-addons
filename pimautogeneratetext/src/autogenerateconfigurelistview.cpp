/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "autogenerateconfigurelistview.h"

AutogenerateConfigureListView::AutogenerateConfigureListView(QWidget *parent)
    : QListView(parent)
{
}

AutogenerateConfigureListView::~AutogenerateConfigureListView() = default;

#include "moc_autogenerateconfigurelistview.cpp"
