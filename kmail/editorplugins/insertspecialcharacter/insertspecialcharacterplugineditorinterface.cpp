/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertspecialcharacterplugineditorinterface.h"
#include <KActionCollection>
#include <KLocalizedString>
#include <KPIMTextEdit/RichTextEditor>
#include <QAction>

InsertSpecialCharacterPluginEditorInterface::InsertSpecialCharacterPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
}

InsertSpecialCharacterPluginEditorInterface::~InsertSpecialCharacterPluginEditorInterface() = default;

void InsertSpecialCharacterPluginEditorInterface::createAction(KActionCollection *ac)
{
    auto action = new QAction(i18n("Insert Special Character..."), this);
    ac->addAction(QStringLiteral("insert_special_character"), action);
    connect(action, &QAction::triggered, this, &InsertSpecialCharacterPluginEditorInterface::slotActivated);
    MessageComposer::PluginActionType type(action, MessageComposer::PluginActionType::Insert);
    setActionType(type);
}

void InsertSpecialCharacterPluginEditorInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void InsertSpecialCharacterPluginEditorInterface::exec()
{
    if (!mSelectSpecialChar) {
        mSelectSpecialChar = new KPIMTextEdit::SelectSpecialCharDialog(parentWidget());
        mSelectSpecialChar->setWindowTitle(i18nc("@title:window", "Insert Special Character"));
        mSelectSpecialChar->setOkButtonText(i18n("Insert"));
        connect(mSelectSpecialChar.data(),
                &KPIMTextEdit::SelectSpecialCharDialog::charSelected,
                this,
                &InsertSpecialCharacterPluginEditorInterface::charSelected);
    }
    mSelectSpecialChar->show();
}

void InsertSpecialCharacterPluginEditorInterface::charSelected(QChar c)
{
    Q_EMIT insertText(c);
}
