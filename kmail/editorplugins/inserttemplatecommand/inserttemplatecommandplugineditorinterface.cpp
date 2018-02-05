/*
   Copyright (C) 2018 Montel Laurent <montel@kde.org>

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

#include "inserttemplatecommandplugineditorinterface.h"
#include <KPIMTextEdit/RichTextEditor>
#include <TemplateParser/TemplatesInsertCommandAction>
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>

InsertTemplateCommandPluginEditorInterface::InsertTemplateCommandPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
}

InsertTemplateCommandPluginEditorInterface::~InsertTemplateCommandPluginEditorInterface()
{
}

void InsertTemplateCommandPluginEditorInterface::createAction(KActionCollection *ac)
{
    TemplateParser::TemplatesInsertCommandAction *action = new TemplateParser::TemplatesInsertCommandAction(this);
    action->setText(i18n("Insert Template Command..."));
    ac->addAction(QStringLiteral("insert_template_command"), action);
    connect(action, &TemplateParser::TemplatesInsertCommandAction::insertCommand, this, &InsertTemplateCommandPluginEditorInterface::slotInsertCommand);
    MessageComposer::ActionType type(action, MessageComposer::ActionType::ToolBar);
    setActionType(type);
}

void InsertTemplateCommandPluginEditorInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void InsertTemplateCommandPluginEditorInterface::exec()
{
    if (!mCommand.isEmpty()) {
        QTextCursor cursor = richTextEditor()->textCursor();
        cursor.insertText(mCommand);
        cursor.setPosition(cursor.position() + mAdjustCursor);
        richTextEditor()->setTextCursor(cursor);
        richTextEditor()->setFocus();
    }
}

void InsertTemplateCommandPluginEditorInterface::slotInsertCommand(const QString &cmd, int adjustCursor)
{
    if (!cmd.isEmpty()) {
        mCommand = cmd;
        mAdjustCursor = adjustCursor;
        slotActivated();
    }
}
