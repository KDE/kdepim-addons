/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "quicktextmenu.h"
using namespace Qt::Literals::StringLiterals;

#include <MessageComposer/ConvertSnippetVariableMenu>
#include <MessageComposer/PluginComposerInterface>
#include <QMenu>

QuickTextMenu::QuickTextMenu(QWidget *parentWidget, QObject *parent)
    : QObject(parent)
    , mParentWidget(parentWidget)
{
    initializeMenu();
}

QuickTextMenu::~QuickTextMenu() = default;

void QuickTextMenu::initializeMenu()
{
    mMenu = new MessageComposer::ConvertSnippetVariableMenu(false, mParentWidget, this);

    connect(mMenu, &MessageComposer::ConvertSnippetVariableMenu::insertVariable, this, [this](MessageComposer::ConvertSnippetVariablesUtil::VariableType type) {
        const QString valueStr = mComposerInterface->convertVariable(type);
        if (!valueStr.isEmpty()) {
            Q_EMIT insertText(valueStr + u' ');
        }
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

#include "moc_quicktextmenu.cpp"
