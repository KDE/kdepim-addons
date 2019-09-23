/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "quicktextmenu.h"
#include <MessageComposer/PluginComposerInterface>
#include <MessageComposer/ConvertSnippetVariableMenu>
#include <QMenu>

QuickTextMenu::QuickTextMenu(QWidget *parentWidget, QObject *parent)
    : QObject(parent)
    , mParentWidget(parentWidget)
{
    initializeMenu();
}

QuickTextMenu::~QuickTextMenu()
{
}

void QuickTextMenu::initializeMenu()
{
    mMenu = new MessageComposer::ConvertSnippetVariableMenu(mParentWidget, this);

    connect(mMenu, &MessageComposer::ConvertSnippetVariableMenu::insertVariable, this, [this](MessageComposer::ConvertSnippetVariablesUtil::VariableType type) {
        Q_EMIT insertText(mComposerInterface->convertVariable(type));
    });
}

QMenu *QuickTextMenu::menu() const
{
    return mMenu->menu();
}

void QuickTextMenu::setPluginComposerInterface(MessageComposer::PluginComposerInterface *composerInterface)
{
    mComposerInterface = composerInterface;
}
