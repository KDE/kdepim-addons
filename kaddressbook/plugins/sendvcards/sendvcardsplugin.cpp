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

#include "sendvcardsplugin.h"
#include "sendvcardsplugininterface.h"
#include <KLocalizedString>
#include <KToggleAction>
#include <kpluginfactory.h>

K_PLUGIN_FACTORY_WITH_JSON(SendVcardsPluginFactory, "kaddressbook_sendvcardsplugin.json", registerPlugin<SendVcardsPlugin>();)

SendVcardsPlugin::SendVcardsPlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::GenericPlugin(parent)
{

}

SendVcardsPlugin::~SendVcardsPlugin()
{
}

PimCommon::GenericPluginInterface *SendVcardsPlugin::createInterface(KActionCollection *ac, QWidget *parent)
{
    SendVcardsPluginInterface *interface = new SendVcardsPluginInterface(this);
    interface->setParentWidget(parent);
    interface->createAction(ac);
    return interface;
}

#include "sendvcardsplugin.moc"
