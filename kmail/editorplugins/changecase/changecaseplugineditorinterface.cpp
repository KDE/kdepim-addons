/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#include "changecaseplugineditorinterface.h"
#include "changecaseeditorplugin_debug.h"
#include <KPIMTextEdit/EditorUtil>
#include <KPIMTextEdit/RichTextEditor>
#include <KActionCollection>
#include <KActionMenuChangeCase>
#include <QAction>

ChangeCasePluginEditorInterface::ChangeCasePluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent),
      mType(Unknown)
{

}

ChangeCasePluginEditorInterface::~ChangeCasePluginEditorInterface()
{

}

void ChangeCasePluginEditorInterface::createAction(KActionCollection *ac)
{
    PimCommon::KActionMenuChangeCase *ChangeCaseMenu = new PimCommon::KActionMenuChangeCase(this);
    ChangeCaseMenu->appendInActionCollection(ac);
    ac->addAction(QStringLiteral("change_case_menu"), ChangeCaseMenu);
    connect(ChangeCaseMenu, &PimCommon::KActionMenuChangeCase::upperCase, this, &ChangeCasePluginEditorInterface::slotUpperCase);
    connect(ChangeCaseMenu, &PimCommon::KActionMenuChangeCase::lowerCase, this, &ChangeCasePluginEditorInterface::slotLowerCase);
    connect(ChangeCaseMenu, &PimCommon::KActionMenuChangeCase::sentenceCase, this, &ChangeCasePluginEditorInterface::slotSentenceCase);
    connect(ChangeCaseMenu, &PimCommon::KActionMenuChangeCase::reverseCase, this, &ChangeCasePluginEditorInterface::slotReverseCase);
    MessageComposer::ActionType type(ChangeCaseMenu, MessageComposer::ActionType::Edit);
    setActionType(type);
}

void ChangeCasePluginEditorInterface::exec()
{
    switch (mType) {
    case Unknown:
        qCDebug(KMAIL_EDITOR_CHANGECASE_PLUGIN_LOG) << " There is an error here. We can't call this plugin with unknown type";
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
