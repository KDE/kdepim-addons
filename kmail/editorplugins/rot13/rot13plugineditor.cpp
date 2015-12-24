/*
  Copyright (c) 2015 Montel Laurent <montel@kde.org>

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


#include "rot13plugineditor.h"
#include "rot13plugineditorinterface.h"
#include <KLocalizedString>
#include <kpluginfactory.h>

K_PLUGIN_FACTORY_WITH_JSON(Rot13PluginEditorFactory, "kmail_rot13editorplugin.json", registerPlugin<Rot13PluginEditor>();)

Rot13PluginEditor::Rot13PluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditor(parent)
{

}

Rot13PluginEditor::~Rot13PluginEditor()
{

}

MessageComposer::PluginEditorInterface *Rot13PluginEditor::createInterface(KActionCollection *ac, QObject *parent)
{
    Rot13PluginEditorInterface *interface = new Rot13PluginEditorInterface(parent);
    interface->createAction(ac);
    //TODO
    return interface;
}

#include "rot13plugineditor.moc"
