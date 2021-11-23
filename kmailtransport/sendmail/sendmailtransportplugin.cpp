/*
    SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "sendmailtransportplugin.h"
#include "sendmailconfigdialog.h"
#include "sendmailjob.h"
#include <KLocalizedString>
#include <KPluginFactory>
#include <QPointer>

K_PLUGIN_CLASS_WITH_JSON(SendMailTransportPlugin, "sendmailtransport.json")

SendMailTransportPlugin::SendMailTransportPlugin(QObject *parent, const QList<QVariant> &)
    : MailTransport::TransportAbstractPlugin(parent)
{
}

SendMailTransportPlugin::~SendMailTransportPlugin() = default;

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
    Q_UNUSED(identifier)
    QPointer<SendMailConfigDialog> transportConfigDialog = new SendMailConfigDialog(transport, parent);
    transportConfigDialog->setWindowTitle(i18nc("@title:window", "Configure account"));
    bool okClicked = (transportConfigDialog->exec() == QDialog::Accepted);
    delete transportConfigDialog;
    return okClicked;
}

MailTransport::TransportJob *SendMailTransportPlugin::createTransportJob(MailTransport::Transport *t, const QString &identifier)
{
    Q_UNUSED(identifier)
    return new MailTransport::SendmailJob(t, this);
}

#include "sendmailtransportplugin.moc"
