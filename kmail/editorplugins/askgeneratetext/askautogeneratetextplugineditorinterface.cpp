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
    ac->addAction(QStringLiteral("change_case_menu"), menu->menu());
    // connect(menu, &AutogenerateConfigureAskMenu::askRequested,)
    /*

    connect(ChangeCaseMenu, &PimCommon::KActionMenuChangeCase::upperCase, this, &AskAutogenerateTextPluginEditorInterface::slotUpperCase);
    connect(ChangeCaseMenu, &PimCommon::KActionMenuChangeCase::lowerCase, this, &AskAutogenerateTextPluginEditorInterface::slotLowerCase);
    connect(ChangeCaseMenu, &PimCommon::KActionMenuChangeCase::sentenceCase, this, &AskAutogenerateTextPluginEditorInterface::slotSentenceCase);
    connect(ChangeCaseMenu, &PimCommon::KActionMenuChangeCase::reverseCase, this, &AskAutogenerateTextPluginEditorInterface::slotReverseCase);
    MessageComposer::PluginActionType type(menu->menu(), MessageComposer::PluginActionType::Edit);
    setActionType(type);
    */
}

void AskAutogenerateTextPluginEditorInterface::exec()
{
    // TODO
}

#include "moc_askautogeneratetextplugineditorinterface.cpp"
