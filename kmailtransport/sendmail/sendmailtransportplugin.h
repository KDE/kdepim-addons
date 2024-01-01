/*
    SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <MailTransport/TransportAbstractPlugin>
#include <QVariant>

class SendMailTransportPlugin : public MailTransport::TransportAbstractPlugin
{
    Q_OBJECT
public:
    explicit SendMailTransportPlugin(QObject *parent = nullptr, const QList<QVariant> & = {});
    ~SendMailTransportPlugin() override;

    [[nodiscard]] QList<MailTransport::TransportAbstractPluginInfo> names() const override;
    bool configureTransport(const QString &identifier, MailTransport::Transport *transport, QWidget *parent) override;
    MailTransport::TransportJob *createTransportJob(MailTransport::Transport *t, const QString &identifier) override;
};
