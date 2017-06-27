/*
    Copyright (c) 2017 Laurent Montel <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "sendmailtransportplugin.h"
#include <kpluginfactory.h>
#include <KLocalizedString>

K_PLUGIN_FACTORY_WITH_JSON(SendMailTransportPluginFactory, "sendmailtransport.json", registerPlugin<SendMailTransportPlugin>();
                           )

SendMailTransportPlugin::SendMailTransportPlugin(QObject *parent, const QList<QVariant> &)
    : MailTransport::TransportAbstractPlugin(parent)
{

}

SendMailTransportPlugin::~SendMailTransportPlugin()
{

}

QString SendMailTransportPlugin::name() const
{
    return i18n("SendMail");
}

bool SendMailTransportPlugin::configureTransport(MailTransport::Transport *transport, QWidget *parent)
{
    //TODO FIXME
    return false;
}

void SendMailTransportPlugin::cleanUp(const QString &identifier)
{
    Q_UNUSED(identifier);
    //TODO FIXME
}

#include "sendmailtransportplugin.moc"
