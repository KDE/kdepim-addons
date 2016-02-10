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

#include "zoomtextplugineditor.h"
#include "zoomtextplugineditorinterface.h"
#include <KLocalizedString>
#include <kpluginfactory.h>

K_PLUGIN_FACTORY_WITH_JSON(ZoomTextPluginEditorFactory, "kmail_zoomtexteditorplugin.json", registerPlugin<ZoomTextPluginEditor>();)

ZoomTextPluginEditor::ZoomTextPluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditor(parent)
{

}

ZoomTextPluginEditor::~ZoomTextPluginEditor()
{

}

MessageComposer::PluginEditorInterface *ZoomTextPluginEditor::createInterface(KActionCollection *ac, QObject *parent)
{
    ZoomTextPluginEditorInterface *interface = new ZoomTextPluginEditorInterface(parent);
    interface->createAction(ac);
    return interface;
}

#include "zoomtextplugineditor.moc"
