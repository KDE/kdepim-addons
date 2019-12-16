/*
   Copyright (C) 2016-2019 Montel Laurent <montel@kde.org>

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

#include "insertspecialcharacterplugineditorinterface.h"
#include <KPIMTextEdit/RichTextEditor>
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>

InsertSpecialCharacterPluginEditorInterface::InsertSpecialCharacterPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
}

InsertSpecialCharacterPluginEditorInterface::~InsertSpecialCharacterPluginEditorInterface()
{
}

void InsertSpecialCharacterPluginEditorInterface::createAction(KActionCollection *ac)
{
    QAction *action = new QAction(i18n("Insert Special Character..."), this);
    ac->addAction(QStringLiteral("insert_special_character"), action);
    connect(action, &QAction::triggered, this, &InsertSpecialCharacterPluginEditorInterface::slotActivated);
    MessageComposer::PluginActionType type(action, MessageComposer::PluginActionType::Edit);
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
        connect(mSelectSpecialChar.data(), &KPIMTextEdit::SelectSpecialCharDialog::charSelected, this, &InsertSpecialCharacterPluginEditorInterface::charSelected);
    }
    mSelectSpecialChar->show();
}

void InsertSpecialCharacterPluginEditorInterface::charSelected(QChar c)
{
    Q_EMIT insertText(c);
}
