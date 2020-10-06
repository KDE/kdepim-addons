/*
   SPDX-FileCopyrightText: 2017 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "itinerarykdeconnecthandler.h"

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QDBusReply>
#include <QUrl>
#include <QVector>
#include <QVersionNumber>

ItineraryKDEConnectHandler::ItineraryKDEConnectHandler(QObject *parent)
    : QObject(parent)
{
}

QVector<ItineraryKDEConnectHandler::Device> ItineraryKDEConnectHandler::devices() const
{
    // TODO we might want to do all this asynchronously by watching change signals and cache the device list

    auto msg = QDBusMessage::createMethodCall(QStringLiteral("org.kde.kdeconnect"), QStringLiteral("/modules/kdeconnect"), QStringLiteral("org.kde.kdeconnect.daemon"), QStringLiteral("devices"));
    msg.setArguments({true, true});
    QDBusPendingReply<QStringList> reply = QDBusConnection::sessionBus().asyncCall(msg);
    reply.waitForFinished();

    if (!reply.isValid()) {
        return {};
    }

    QVector<Device> devices;
    const auto values = reply.value();
    for (const QString &deviceId : values) {
        QDBusInterface deviceIface(QStringLiteral("org.kde.kdeconnect"), QStringLiteral("/modules/kdeconnect/devices/") + deviceId, QStringLiteral("org.kde.kdeconnect.device"));
        QDBusReply<bool> pluginReply = deviceIface.call(QStringLiteral("hasPlugin"), QLatin1String("kdeconnect_share"));

        if (pluginReply.value()) {
            devices.push_back({deviceId, deviceIface.property("name").toString()});
        }
    }

    return devices;
}

void ItineraryKDEConnectHandler::sendToDevice(const QString &fileName, const QString &deviceId)
{
    const QDBusInterface remoteApp(QStringLiteral("org.kde.kdeconnect"), QStringLiteral("/MainApplication"), QStringLiteral("org.qtproject.Qt.QCoreApplication"));
    QVersionNumber kdeconnectVersion = QVersionNumber::fromString(remoteApp.property("applicationVersion").toString());

    QString method;
    if (kdeconnectVersion >= QVersionNumber(1, 4, 0)) {
        method = QStringLiteral("openFile");
    } else {
        method = QStringLiteral("shareUrl");
    }

    QDBusMessage msg = QDBusMessage::createMethodCall(QStringLiteral("org.kde.kdeconnect"),
                                                      QStringLiteral("/modules/kdeconnect/devices/") + deviceId + QStringLiteral("/share"),
                                                      QStringLiteral("org.kde.kdeconnect.device.share"), method);
    msg.setArguments({QUrl::fromLocalFile(fileName).toString()});

    QDBusConnection::sessionBus().send(msg);
}
