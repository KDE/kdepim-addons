/*
   Copyright (C) 2016-2018 Montel Laurent <montel@kde.org>

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

#include "nonbreakingspaceplugineditorinterface.h"
#include <KPIMTextEdit/RichTextEditor>
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>

NonBreakingSpacePluginEditorInterface::NonBreakingSpacePluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
}

NonBreakingSpacePluginEditorInterface::~NonBreakingSpacePluginEditorInterface()
{
}

void NonBreakingSpacePluginEditorInterface::createAction(KActionCollection *ac)
{
    QAction *action = new QAction(i18n("Insert Non Breaking Space"), this);
    ac->addAction(QStringLiteral("insert_non_breaking_space"), action);
    ac->setDefaultShortcut(action, Qt::CTRL + Qt::Key_Space);
    connect(action, &QAction::triggered, this, &NonBreakingSpacePluginEditorInterface::slotActivated);
    MessageComposer::ActionType type(action, MessageComposer::ActionType::Edit);
    setActionType(type);
}

void NonBreakingSpacePluginEditorInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void NonBreakingSpacePluginEditorInterface::exec()
{
    richTextEditor()->insertPlainText(QChar(0x000A0));
}
