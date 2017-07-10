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
#include "sendmailconfigdialog.h"
#include "sendmailjob.h"
#include <kpluginfactory.h>
#include <KLocalizedString>
#include <QPointer>

K_PLUGIN_FACTORY_WITH_JSON(SendMailTransportPluginFactory, "sendmailtransport.json", registerPlugin<SendMailTransportPlugin>();
                           )

SendMailTransportPlugin::SendMailTransportPlugin(QObject *parent, const QList<QVariant> &)
    : MailTransport::TransportAbstractPlugin(parent)
{
}

SendMailTransportPlugin::~SendMailTransportPlugin()
{
}

QVector<MailTransport::TransportAbstractPluginInfo> SendMailTransportPlugin::names() const
{
    MailTransport::TransportAbstractPluginInfo info;
    info.name = i18nc("@option sendmail transport", "Sendmail");
    info.identifier = QStringLiteral("sendmail");
    info.description = i18n("A local sendmail installation");
    info.isAkonadi = false;
    return QVector<MailTransport::TransportAbstractPluginInfo>() << info;
}

bool SendMailTransportPlugin::configureTransport(const QString &identifier, MailTransport::Transport *transport, QWidget *parent)
{
    Q_UNUSED(identifier);
    QPointer<SendMailConfigDialog> transportConfigDialog
        = new SendMailConfigDialog(transport, parent);
    transportConfigDialog->setWindowTitle(i18n("Configure account"));
    bool okClicked = (transportConfigDialog->exec() == QDialog::Accepted);
    delete transportConfigDialog;
    return okClicked;
}

MailTransport::TransportJob *SendMailTransportPlugin::createTransportJob(MailTransport::Transport *t, const QString &identifier)
{
    Q_UNUSED(identifier);
    return new MailTransport::SendmailJob(t, this);
}

#include "sendmailtransportplugin.moc"


