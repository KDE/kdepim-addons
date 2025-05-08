/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "askautogeneratetextplugineditorinterface.h"
#include <KActionCollection>
#include <PimAutoGenerateText/AutogenerateConfigureAskManager>
#include <PimAutoGenerateText/AutogenerateConfigureAskMenu>
#include <QAction>
#include <QMenu>
#include <TextCustomEditor/RichTextEditor>

AskAutogenerateTextPluginEditorInterface::AskAutogenerateTextPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
    , mAskManager(new AutogenerateConfigureAskManager(this))
{
    setNeedSelectedText(true);
}

AskAutogenerateTextPluginEditorInterface::~AskAutogenerateTextPluginEditorInterface() = default;

void AskAutogenerateTextPluginEditorInterface::createAction(KActionCollection *ac)
{
    auto menu = new AutogenerateConfigureAskMenu(mAskManager, this);
    ac->addAction(QStringLiteral("editor_ask_ia"), menu);
    connect(menu, &AutogenerateConfigureAskMenu::askRequested, this, &AskAutogenerateTextPluginEditorInterface::slotAskRequested);
    MessageComposer::PluginActionType type(menu, MessageComposer::PluginActionType::Edit);
    setActionType(type);
}

void AskAutogenerateTextPluginEditorInterface::slotAskRequested(const QString &msg)
{
    // TODO
}

void AskAutogenerateTextPluginEditorInterface::exec()
{
    // TODO
}

#include "moc_askautogeneratetextplugineditorinterface.cpp"
