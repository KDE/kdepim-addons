/*
   Copyright (C) 2016-2019 Montel Laurent <montel@kde.org>

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

#include "quicktextplugineditor.h"
#include "quicktextplugineditorinterface.h"
#include <kpluginfactory.h>
#include "quicktextconfiguredialog.h"

K_PLUGIN_CLASS_WITH_JSON(QuickTextPluginEditor, "kmail_quicktextplugin.json")

QuickTextPluginEditor::QuickTextPluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditor(parent)
{
}

QuickTextPluginEditor::~QuickTextPluginEditor()
{
}

MessageComposer::PluginEditorInterface *QuickTextPluginEditor::createInterface(QObject *parent)
{
    QuickTextPluginEditorInterface *interface = new QuickTextPluginEditorInterface(parent);
    return interface;
}

bool QuickTextPluginEditor::hasStatusBarSupport() const
{
    return true;
}

bool QuickTextPluginEditor::hasConfigureDialog() const
{
    return true;
}

void QuickTextPluginEditor::showConfigureDialog(QWidget *parent)
{
    QPointer<QuickTextConfigureDialog> dlg = new QuickTextConfigureDialog(parent);
    if (dlg->exec()) {
        //TODO Q_EMIT configChanged();
    }
    delete dlg;
}

bool QuickTextPluginEditor::canProcessKeyEvent() const
{
    return true;
}

#include "quicktextplugineditor.moc"


