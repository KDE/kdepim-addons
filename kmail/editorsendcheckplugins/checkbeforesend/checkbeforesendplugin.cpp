/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#include "checkbeforesendplugin.h"
#include "checkbeforesendinterface.h"
#include "checkbeforesendconfigurewidget.h"

#include <KLocalizedString>
#include <kpluginfactory.h>

K_PLUGIN_FACTORY_WITH_JSON(ChangeCasePluginEditorFactory, "kmail_checkbeforesendplugin.json", registerPlugin<CheckBeforeSendPlugin>();)

CheckBeforeSendPlugin::CheckBeforeSendPlugin(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditorCheckBeforeSend(parent)
{

}

CheckBeforeSendPlugin::~CheckBeforeSendPlugin()
{

}

MessageComposer::PluginEditorCheckBeforeSendInterface *CheckBeforeSendPlugin::createInterface(QObject *parent)
{
    CheckBeforeSendInterface *interface = new CheckBeforeSendInterface(parent);
    connect(this, &CheckBeforeSendPlugin::configChanged, interface, &CheckBeforeSendInterface::reloadConfig);
    return interface;
}

bool CheckBeforeSendPlugin::hasConfigureSupport() const
{
    return true;
}

MessageComposer::PluginEditorCheckBeforeSendConfigureWidgetSetting CheckBeforeSendPlugin::createConfigureWidget(QWidget *parent) const
{
    CheckBeforeSendConfigureWidget *w = new CheckBeforeSendConfigureWidget(parent);
    MessageComposer::PluginEditorCheckBeforeSendConfigureWidgetSetting settings(w, i18n("Check Before Send Email"));
    return settings;
}

#include "checkbeforesendplugin.moc"
