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
#include <MessageComposer/PluginEditorConverterInitialData>
#include <KPIMTextEdit/RichTextComposer>
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>
#include <QWidgetAction>
#include <QMenu>
#include <KMessageBox>

InsertTemplateCommandPluginEditorInterface::InsertTemplateCommandPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorConvertTextInterface(parent)
{
}

InsertTemplateCommandPluginEditorInterface::~InsertTemplateCommandPluginEditorInterface()
{
}

void InsertTemplateCommandPluginEditorInterface::createAction(KActionCollection *ac)
{
    mCommandAction = new TemplateParser::TemplatesInsertCommandAction(this);
    mCommandAction->setType(TemplateParser::TemplatesCommandMenu::CurrentMessage);
    mToolButton = new QToolButton;
    mToolButton->setMenu(mCommandAction->menu());

    mToolButton->setText(i18n("Insert Template Command..."));
    mToolButton->setPopupMode(QToolButton::InstantPopup);
    mCommandAction->setDefaultWidget(mToolButton);
    ac->addAction(QStringLiteral("insert_template_command"), mCommandAction);
    connect(mCommandAction, &TemplateParser::TemplatesInsertCommandAction::insertCommand, this, &InsertTemplateCommandPluginEditorInterface::slotInsertCommand);
    MessageComposer::PluginActionType type(mCommandAction, MessageComposer::PluginActionType::ToolBar);
    setActionTypes(type);
}

void InsertTemplateCommandPluginEditorInterface::slotOpenMenu()
{
    mCommandAction->menu()->exec(QCursor::pos());
}

void InsertTemplateCommandPluginEditorInterface::slotInsertCommand(const QString &cmd, int adjustCursor)
{
    if (!cmd.isEmpty()) {
        QTextCursor cursor = richTextEditor()->textCursor();
        cursor.insertText(cmd);
        cursor.setPosition(cursor.position() + adjustCursor);
        richTextEditor()->setTextCursor(cursor);
        richTextEditor()->setFocus();
    }
}

MessageComposer::PluginEditorConvertTextInterface::ConvertTextStatus InsertTemplateCommandPluginEditorInterface::convertTextToFormat(MessageComposer::TextPart *textPart)
{
    Q_UNUSED(textPart);
    return MessageComposer::PluginEditorConvertTextInterface::ConvertTextStatus::NotConverted;
}

bool InsertTemplateCommandPluginEditorInterface::reformatText()
{
    //TODO use templateparser.
    //TODO we need to reformat text and change text.
    //We need to reformat text.
    return true;
}

void InsertTemplateCommandPluginEditorInterface::setInitialData(const MessageComposer::PluginEditorConverterInitialData &data)
{
    MessageComposer::PluginEditorConvertTextInterface::setInitialData(data);
    TemplateParser::TemplatesCommandMenu::MenuTypes type;
    type |= TemplateParser::TemplatesCommandMenu::CurrentMessage;
    if (!data.newMessage()) {
        type |= TemplateParser::TemplatesCommandMenu::ReplyForwardMessage;
    }
    mCommandAction->setType(type);
    mToolButton->setMenu(mCommandAction->menu());
}
