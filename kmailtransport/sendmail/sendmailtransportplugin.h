/*
    SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef SENDMAILTRANSPORTPLUGIN_H
#define SENDMAILTRANSPORTPLUGIN_H

#include <MailTransport/TransportAbstractPlugin>
#include <QVariant>

class SendMailTransportPlugin : public MailTransport::TransportAbstractPlugin
{
    Q_OBJECT
public:
    explicit SendMailTransportPlugin(QObject *parent = nullptr, const QList<QVariant> & = {});
    ~SendMailTransportPlugin() override;

    QVector<MailTransport::TransportAbstractPluginInfo> names() const override;
    bool configureTransport(const QString &identifier, MailTransport::Transport *transport, QWidget *parent) override;
    MailTransport::TransportJob *createTransportJob(MailTransport::Transport *t, const QString &identifier) override;
};

#endif
