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
#include <KPIMTextEdit/RichTextEditor>
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>

changecasePluginEditorInterface::changecasePluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{

}

changecasePluginEditorInterface::~changecasePluginEditorInterface()
{

}

void changecasePluginEditorInterface::createAction(KActionCollection *ac)
{
    QAction *action = new QAction(i18n("Insert Special Character..."), this);
    ac->addAction(QStringLiteral("insert_special_character"), action);
    connect(action, &QAction::triggered, this, &changecasePluginEditorInterface::slotActivated);
    MessageComposer::ActionType type(action, MessageComposer::ActionType::Edit);
    setActionType(type);
}

void changecasePluginEditorInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void changecasePluginEditorInterface::exec()
{
}

