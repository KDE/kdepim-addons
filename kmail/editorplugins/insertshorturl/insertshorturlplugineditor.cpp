/*
   Copyright (C) 2017 Montel Laurent <montel@kde.org>

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

#include "insertshorturlplugineditor.h"
#include "insertshorturlplugineditorinterface.h"
#include "insertshorturlconfiguredialog.h"
#include <kpluginfactory.h>
#include <QPointer>

K_PLUGIN_FACTORY_WITH_JSON(InsertShorturlPluginEditorFactory, "kmail_insertshorturleditorplugin.json", registerPlugin<InsertShorturlPluginEditor>();
                           )

InsertShorturlPluginEditor::InsertShorturlPluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditor(parent)
{

}

InsertShorturlPluginEditor::~InsertShorturlPluginEditor()
{
}

MessageComposer::PluginEditorInterface *InsertShorturlPluginEditor::createInterface(KActionCollection *ac, QObject *parent)
{
    InsertShorturlPluginEditorInterface *interface = new InsertShorturlPluginEditorInterface(parent);
    interface->createAction(ac);
    return interface;
}

bool InsertShorturlPluginEditor::hasPopupMenuSupport() const
{
    return true;
}

bool InsertShorturlPluginEditor::hasConfigureDialog() const
{
    return true;
}

void InsertShorturlPluginEditor::showConfigureDialog(QWidget *parent)
{
    QPointer<InsertShorturlConfigureDialog> dlg = new InsertShorturlConfigureDialog(parent);
    dlg->exec();
    delete dlg;
}

#include "insertshorturlplugineditor.moc"
