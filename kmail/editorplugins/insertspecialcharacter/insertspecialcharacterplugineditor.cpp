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

#include "insertspecialcharacterplugineditor.h"
#include "insertspecialcharacterplugineditorinterface.h"
#include <kpluginfactory.h>

K_PLUGIN_CLASS_WITH_JSON(InsertSpecialCharacterPluginEditor, "kmail_insertspecialcharactereditorplugin.json")

InsertSpecialCharacterPluginEditor::InsertSpecialCharacterPluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditor(parent)
{
}

InsertSpecialCharacterPluginEditor::~InsertSpecialCharacterPluginEditor()
{
}

MessageComposer::PluginEditorInterface *InsertSpecialCharacterPluginEditor::createInterface(KActionCollection *ac, QObject *parent)
{
    InsertSpecialCharacterPluginEditorInterface *interface = new InsertSpecialCharacterPluginEditorInterface(parent);
    interface->createAction(ac);
    return interface;
}

#include "insertspecialcharacterplugineditor.moc"
