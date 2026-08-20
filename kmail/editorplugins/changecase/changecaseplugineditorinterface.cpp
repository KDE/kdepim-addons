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
    case SentenceCase:
        sentenceCase();
        break;
    case ReverseCase:
        reverseCase();
        break;
    }
    mType = Unknown;
}

void ChangeCasePluginEditorInterface::applyChangeCase(void (*convert)(QTextCursor &))
{
    auto editor = richTextEditor();
    if (!editor) {
        qCWarning(KMAIL_EDITOR_CHANGECASE_PLUGIN_LOG) << "Editor is null, we can't apply change case";
        return;
    }
    QTextCursor textCursor = editor->textCursor();
    if (!textCursor.hasSelection()) {
        qCWarning(KMAIL_EDITOR_CHANGECASE_PLUGIN_LOG) << "No text selected, we can't apply change case";
        return;
    }
    const int start = textCursor.selectionStart();
    convert(textCursor);
    const int end = textCursor.position();
    textCursor.setPosition(start);
    textCursor.setPosition(end, QTextCursor::KeepAnchor);
    editor->setTextCursor(textCursor);
}

void ChangeCasePluginEditorInterface::sentenceCase()
{
    applyChangeCase(&TextUtils::ConvertText::sentenceCase);
}

void ChangeCasePluginEditorInterface::upperCase()
{
    applyChangeCase(&TextUtils::ConvertText::upperCase);
}

void ChangeCasePluginEditorInterface::lowerCase()
{
    applyChangeCase(&TextUtils::ConvertText::lowerCase);
}

void ChangeCasePluginEditorInterface::reverseCase()
{
    applyChangeCase(&TextUtils::ConvertText::reverseCase);
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
    mType = SentenceCase;
    Q_EMIT emitPluginActivated(this);
}

void ChangeCasePluginEditorInterface::slotReverseCase()
{
    mType = ReverseCase;
    Q_EMIT emitPluginActivated(this);
}

#include "moc_changecaseplugineditorinterface.cpp"
