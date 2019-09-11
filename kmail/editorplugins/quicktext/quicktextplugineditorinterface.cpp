/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

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

#include "quicktextplugineditorinterface.h"
#include "quicktextmenu.h"
#include <KPIMTextEdit/RichTextEditor>
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>

QuickTextPluginEditorInterface::QuickTextPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
}

QuickTextPluginEditorInterface::~QuickTextPluginEditorInterface()
{
}

void QuickTextPluginEditorInterface::createAction(KActionCollection *ac)
{
    QuickTextMenu *quickTextMenu = new QuickTextMenu(parentWidget(), this);
    quickTextMenu->setPluginComposerInterface(composerInterface());
    QAction *action = new QAction(i18n("Variables"), this);
    action->setMenu(quickTextMenu->menu());
    ac->addAction(QStringLiteral("insert_variables"), action);
    connect(action, &QAction::triggered, this, &QuickTextPluginEditorInterface::slotActivated);
    MessageComposer::PluginActionType type(action, MessageComposer::PluginActionType::Edit);
    setActionType(type);
    //Add widget setStatusBarWidget()
}

void QuickTextPluginEditorInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void QuickTextPluginEditorInterface::exec()
{
}
