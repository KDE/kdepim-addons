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
    QAction *action = new QAction(i18n("Insert Special Character..."), this);
    ac->addAction(QStringLiteral("insert_special_character"), action);
    connect(action, &QAction::triggered, this, &InsertTemplateCommandPluginEditorInterface::slotActivated);
    MessageComposer::ActionType type(action, MessageComposer::ActionType::Edit);
    setActionType(type);
}

void InsertTemplateCommandPluginEditorInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void InsertTemplateCommandPluginEditorInterface::exec()
{
}

void InsertTemplateCommandPluginEditorInterface::charSelected(QChar c)
{
    richTextEditor()->insertPlainText(c);
}
