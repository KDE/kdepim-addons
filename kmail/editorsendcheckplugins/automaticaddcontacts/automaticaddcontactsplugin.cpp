/*
   Copyright (C) 2016-2020 Laurent Montel <montel@kde.org>

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

#include "automaticaddcontactsplugin.h"
#include "automaticaddcontactsinterface.h"
#include "automaticaddcontactsconfigurewidget.h"
#include "automaticaddcontactsconfiguredialog.h"

#include <QPointer>
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(AutomaticAddContactsPlugin, "kmail_automaticaddcontactsplugin.json")
AutomaticAddContactsPlugin::AutomaticAddContactsPlugin(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditorCheckBeforeSend(parent)
{
}

AutomaticAddContactsPlugin::~AutomaticAddContactsPlugin()
{
}

MessageComposer::PluginEditorCheckBeforeSendInterface *AutomaticAddContactsPlugin::createInterface(QObject *parent)
{
    AutomaticAddContactsInterface *interface = new AutomaticAddContactsInterface(parent);
    connect(this, &AutomaticAddContactsPlugin::configChanged, interface, &AutomaticAddContactsInterface::reloadConfig);
    return interface;
}

bool AutomaticAddContactsPlugin::hasConfigureDialog() const
{
    return true;
}

void AutomaticAddContactsPlugin::showConfigureDialog(QWidget *parent)
{
    QPointer<AutomaticAddContactsConfigureDialog> dlg = new AutomaticAddContactsConfigureDialog(parent);
    dlg->exec();
    delete dlg;
}

#include "automaticaddcontactsplugin.moc"
