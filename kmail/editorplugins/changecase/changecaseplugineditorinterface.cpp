/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "changecaseplugineditorinterface.h"
#include <KPIMTextEdit/EditorUtil>
#include <KPIMTextEdit/RichTextEditor>
#include <KLocalizedString>
#include <KActionCollection>
#include <KActionMenuChangeCase>
#include <QAction>
#include <QDebug>

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
    switch(mType) {
    case Unknown:
        qDebug() << " There is an error here. We can't call this plugin with unknown type";
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
