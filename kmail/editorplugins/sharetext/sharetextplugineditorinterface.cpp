/*
   Copyright (C) 2018-2020 Laurent Montel <montel@kde.org>

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

#include "sharetextplugineditorinterface.h"
#include "sharetexteditorplugin_debug.h"
#include "sharetextpurposemenuwidget.h"
#include <KPIMTextEdit/EditorUtil>
#include <KPIMTextEdit/RichTextEditor>
#include <KActionCollection>
#include <KActionMenuChangeCase>
#include <KLocalizedString>
#include <KActionMenu>
#include <QAction>

ShareTextPluginEditorInterface::ShareTextPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
    setNeedSelectedText(false);
}

ShareTextPluginEditorInterface::~ShareTextPluginEditorInterface()
{
}

void ShareTextPluginEditorInterface::createAction(KActionCollection *ac)
{
    SharetextPurposeMenuWidget *purposeMenu = new SharetextPurposeMenuWidget(parentWidget(), this);
    KActionMenu *shareAction = new KActionMenu(i18n("Share Mail Text..."), this);
    shareAction->setMenu(purposeMenu->menu());
    shareAction->setIcon(QIcon::fromTheme(QStringLiteral("document-share")));
    shareAction->setDelayed(false);
    ac->addAction(QStringLiteral("share_text_menu"), shareAction);
    purposeMenu->setEditorWidget(this);
    MessageComposer::PluginActionType type(shareAction, MessageComposer::PluginActionType::File);
    setActionType(type);
}

void ShareTextPluginEditorInterface::exec()
{
    //Nothing
}
