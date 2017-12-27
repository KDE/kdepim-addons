/*
   Copyright (C) 2017 Montel Laurent <montel@kde.org>

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

#include "insertshorturlplugineditorinterface.h"
#include <KPIMTextEdit/RichTextEditor>
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>

InsertShorturlPluginEditorInterface::InsertShorturlPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
}

InsertShorturlPluginEditorInterface::~InsertShorturlPluginEditorInterface()
{
}

void InsertShorturlPluginEditorInterface::createAction(KActionCollection *ac)
{
    QAction *action = new QAction(i18n("Insert Short Url..."), this);
    ac->addAction(QStringLiteral("insert_shortulr"), action);
    connect(action, &QAction::triggered, this, &InsertShorturlPluginEditorInterface::slotActivated);
    MessageComposer::ActionType type(action, MessageComposer::ActionType::PopupMenu);
    setActionType(type);
}

void InsertShorturlPluginEditorInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void InsertShorturlPluginEditorInterface::exec()
{
    QTextCursor textCursor = richTextEditor()->textCursor();
    if (textCursor.hasSelection()) {
        QString urlStr = textCursor.selectedText();
        if (urlStr.startsWith(QLatin1String("http:")) || urlStr.startsWith(QLatin1String("https:"))) {
            //textCursor.insertText(newText);
        }
    }
    //editorUtil.upperCase(textCursor);

}
