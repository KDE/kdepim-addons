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

#include "changecaseplugineditor.h"
#include "changecaseplugineditorinterface.h"
#include <KLocalizedString>
#include <kpluginfactory.h>

K_PLUGIN_FACTORY_WITH_JSON(ChangeCasePluginEditorFactory, "kmail_changecaseeditorplugin.json", registerPlugin<ChangeCasePluginEditor>();)

ChangeCasePluginEditor::ChangeCasePluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditor(parent)
{

}

ChangeCasePluginEditor::~ChangeCasePluginEditor()
{

}

MessageComposer::PluginEditorInterface *ChangeCasePluginEditor::createInterface(KActionCollection *ac, QObject *parent)
{
    ChangeCasePluginEditorInterface *interface = new ChangeCasePluginEditorInterface(parent);
    interface->createAction(ac);
    return interface;
}

#include "changecaseplugineditor.moc"
