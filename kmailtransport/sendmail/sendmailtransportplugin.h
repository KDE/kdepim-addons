/*
    Copyright (C) 2017-2018 Laurent Montel <montel@kde.org>

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

#ifndef SENDMAILTRANSPORTPLUGIN_H
#define SENDMAILTRANSPORTPLUGIN_H

#include <MailTransport/TransportAbstractPlugin>
#include <QVariant>

class SendMailTransportPlugin : public MailTransport::TransportAbstractPlugin
{
    Q_OBJECT
public:
    explicit SendMailTransportPlugin(QObject *parent = nullptr, const QList<QVariant> & =
    {
    });
    ~SendMailTransportPlugin() override;

    QVector<MailTransport::TransportAbstractPluginInfo> names() const override;
    bool configureTransport(const QString &identifier, MailTransport::Transport *transport, QWidget *parent) override;
    MailTransport::TransportJob *createTransportJob(MailTransport::Transport *t, const QString &identifier) override;
};

#endif
