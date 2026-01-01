/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "changecaseplugineditorinterface.h"
using namespace Qt::Literals::StringLiterals;

#include "changecaseeditorplugin_debug.h"
#include <KActionCollection>
#include <PimCommon/KActionMenuChangeCase>
#include <QAction>
#include <TextCustomEditor/RichTextEditor>
#include <TextUtils/ConvertText>

ChangeCasePluginEditorInterface::ChangeCasePluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
    setNeedSelectedText(true);
}

ChangeCasePluginEditorInterface::~ChangeCasePluginEditorInterface() = default;

void ChangeCasePluginEditorInterface::createAction(KActionCollection *ac)
{
    auto changeCaseMenu = new PimCommon::KActionMenuChangeCase(this);
    changeCaseMenu->appendInActionCollection(ac);
    ac->addAction(u"change_case_menu"_s, changeCaseMenu);
    connect(changeCaseMenu, &PimCommon::KActionMenuChangeCase::upperCase, this, &ChangeCasePluginEditorInterface::slotUpperCase);
    connect(changeCaseMenu, &PimCommon::KActionMenuChangeCase::lowerCase, this, &ChangeCasePluginEditorInterface::slotLowerCase);
    connect(changeCaseMenu, &PimCommon::KActionMenuChangeCase::sentenceCase, this, &ChangeCasePluginEditorInterface::slotSentenceCase);
    connect(changeCaseMenu, &PimCommon::KActionMenuChangeCase::reverseCase, this, &ChangeCasePluginEditorInterface::slotReverseCase);
    MessageComposer::PluginActionType type(changeCaseMenu, MessageComposer::PluginActionType::Edit);
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
    TextUtils::ConvertText::sentenceCase(textCursor);
}

void ChangeCasePluginEditorInterface::upperCase()
{
    QTextCursor textCursor = richTextEditor()->textCursor();
    TextUtils::ConvertText::upperCase(textCursor);
}

void ChangeCasePluginEditorInterface::lowerCase()
{
    QTextCursor textCursor = richTextEditor()->textCursor();
    TextUtils::ConvertText::lowerCase(textCursor);
}

void ChangeCasePluginEditorInterface::reverseCase()
{
    QTextCursor textCursor = richTextEditor()->textCursor();
    TextUtils::ConvertText::reverseCase(textCursor);
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

#include "moc_changecaseplugineditorinterface.cpp"
