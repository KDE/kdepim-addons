/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autogenerateconfigureaskmenu.h"
#include <QMenu>

AutogenerateConfigureAskMenu::AutogenerateConfigureAskMenu(QObject *parent)
    : QObject{parent}
{
}

AutogenerateConfigureAskMenu::~AutogenerateConfigureAskMenu() = default;

QWidget *AutogenerateConfigureAskMenu::parentWidget() const
{
    return mParentWidget;
}

void AutogenerateConfigureAskMenu::setParentWidget(QWidget *newParentWidget)
{
    mParentWidget = newParentWidget;
}

#include "moc_autogenerateconfigureaskmenu.cpp"
