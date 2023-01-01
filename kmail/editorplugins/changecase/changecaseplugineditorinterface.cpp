/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "changecaseplugineditorinterface.h"
#include "changecaseeditorplugin_debug.h"
#include <KActionCollection>
#include <KPIMTextEdit/EditorUtil>
#include <KPIMTextEdit/RichTextEditor>
#include <PimCommon/KActionMenuChangeCase>
#include <QAction>

ChangeCasePluginEditorInterface::ChangeCasePluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
    setNeedSelectedText(true);
}

ChangeCasePluginEditorInterface::~ChangeCasePluginEditorInterface() = default;

void ChangeCasePluginEditorInterface::createAction(KActionCollection *ac)
{
    auto ChangeCaseMenu = new PimCommon::KActionMenuChangeCase(this);
    ChangeCaseMenu->appendInActionCollection(ac);
    ac->addAction(QStringLiteral("change_case_menu"), ChangeCaseMenu);
    connect(ChangeCaseMenu, &PimCommon::KActionMenuChangeCase::upperCase, this, &ChangeCasePluginEditorInterface::slotUpperCase);
    connect(ChangeCaseMenu, &PimCommon::KActionMenuChangeCase::lowerCase, this, &ChangeCasePluginEditorInterface::slotLowerCase);
    connect(ChangeCaseMenu, &PimCommon::KActionMenuChangeCase::sentenceCase, this, &ChangeCasePluginEditorInterface::slotSentenceCase);
    connect(ChangeCaseMenu, &PimCommon::KActionMenuChangeCase::reverseCase, this, &ChangeCasePluginEditorInterface::slotReverseCase);
    MessageComposer::PluginActionType type(ChangeCaseMenu, MessageComposer::PluginActionType::Edit);
    setActionType(type);
}

void ChangeCasePluginEditorInterface::exec()
{
    switch (mType) {
    case Unknown:
        qCWarning(KMAIL_EDITOR_CHANGECASE_PLUGIN_LOG) << " There is an error here. We can't call this plugin with unknown type";
        break;
    case UpperCase:
        upperCase();
        break;
    case LowerCase:
        lowerCase();
        break;
    case SentenseCase:
        sentenceCase();
        break;
    case ReverseCase:
        reverseCase();
        break;
    }
    mType = Unknown;
}

void ChangeCasePluginEditorInterface::sentenceCase()
{
    QTextCursor textCursor = richTextEditor()->textCursor();
    KPIMTextEdit::EditorUtil editorUtil;
    editorUtil.sentenceCase(textCursor);
}

void ChangeCasePluginEditorInterface::upperCase()
{
    KPIMTextEdit::EditorUtil editorUtil;
    QTextCursor textCursor = richTextEditor()->textCursor();
    editorUtil.upperCase(textCursor);
}

void ChangeCasePluginEditorInterface::lowerCase()
{
    QTextCursor textCursor = richTextEditor()->textCursor();
    KPIMTextEdit::EditorUtil editorUtil;
    editorUtil.lowerCase(textCursor);
}

void ChangeCasePluginEditorInterface::reverseCase()
{
    QTextCursor textCursor = richTextEditor()->textCursor();
    KPIMTextEdit::EditorUtil editorUtil;
    editorUtil.reverseCase(textCursor);
}

void ChangeCasePluginEditorInterface::slotUpperCase()
{
    mType = UpperCase;
    Q_EMIT emitPluginActivated(this);
}

void ChangeCasePluginEditorInterface::slotLowerCase()
{
    mType = LowerCase;
    Q_EMIT emitPluginActivated(this);
}

void ChangeCasePluginEditorInterface::slotSentenceCase()
{
    mType = SentenseCase;
    Q_EMIT emitPluginActivated(this);
}

void ChangeCasePluginEditorInterface::slotReverseCase()
{
    mType = ReverseCase;
    Q_EMIT emitPluginActivated(this);
}
