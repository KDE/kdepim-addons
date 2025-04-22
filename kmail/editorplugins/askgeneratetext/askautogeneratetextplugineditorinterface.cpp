/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "askautogeneratetextplugineditorinterface.h"
#include <KActionCollection>
#include <QAction>
#include <TextCustomEditor/RichTextEditor>

AskAutogenerateTextPluginEditorInterface::AskAutogenerateTextPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
    setNeedSelectedText(true);
}

AskAutogenerateTextPluginEditorInterface::~AskAutogenerateTextPluginEditorInterface() = default;

void AskAutogenerateTextPluginEditorInterface::createAction(KActionCollection *ac)
{
    /*
    auto ChangeCaseMenu = new PimCommon::KActionMenuChangeCase(this);
    ChangeCaseMenu->appendInActionCollection(ac);
    ac->addAction(QStringLiteral("change_case_menu"), ChangeCaseMenu);
    connect(ChangeCaseMenu, &PimCommon::KActionMenuChangeCase::upperCase, this, &AskAutogenerateTextPluginEditorInterface::slotUpperCase);
    connect(ChangeCaseMenu, &PimCommon::KActionMenuChangeCase::lowerCase, this, &AskAutogenerateTextPluginEditorInterface::slotLowerCase);
    connect(ChangeCaseMenu, &PimCommon::KActionMenuChangeCase::sentenceCase, this, &AskAutogenerateTextPluginEditorInterface::slotSentenceCase);
    connect(ChangeCaseMenu, &PimCommon::KActionMenuChangeCase::reverseCase, this, &AskAutogenerateTextPluginEditorInterface::slotReverseCase);
    MessageComposer::PluginActionType type(ChangeCaseMenu, MessageComposer::PluginActionType::Edit);
    setActionType(type);
    */
}

void AskAutogenerateTextPluginEditorInterface::exec()
{
    // TODO
}

#include "moc_askautogeneratetextplugineditorinterface.cpp"
