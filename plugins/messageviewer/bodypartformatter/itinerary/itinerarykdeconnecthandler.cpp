/*
   SPDX-FileCopyrightText: 2017 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "itinerarykdeconnecthandler.h"

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QDBusReply>
#include <QList>
#include <QUrl>
using namespace Qt::Literals::StringLiterals;

ItineraryKDEConnectHandler::ItineraryKDEConnectHandler(QObject *parent)
    : QObject(parent)
{
}

QList<ItineraryKDEConnectHandler::Device> ItineraryKDEConnectHandler::devices() const
{
    // TODO we might want to do all this asynchronously by watching change signals and cache the device list

    auto msg = QDBusMessage::createMethodCall(u"org.kde.kdeconnect"_s, u"/modules/kdeconnect"_s, u"org.kde.kdeconnect.daemon"_s, u"devices"_s);
    msg.setArguments({true, true});
    QDBusPendingReply<QStringList> reply = QDBusConnection::sessionBus().asyncCall(msg);
    reply.waitForFinished();

    if (!reply.isValid()) {
        return {};
    }

    QList<Device> devices;
    const auto values = reply.value();
    for (const QString &deviceId : values) {
        QDBusInterface deviceIface(u"org.kde.kdeconnect"_s, u"/modules/kdeconnect/devices/"_s + deviceId, u"org.kde.kdeconnect.device"_s);
        QDBusReply<bool> pluginReply = deviceIface.call(u"hasPlugin"_s, QLatin1StringView("kdeconnect_share"));

        if (pluginReply.value()) {
            devices.push_back({deviceId, deviceIface.property("name").toString()});
        }
    }

    return devices;
}

void ItineraryKDEConnectHandler::sendToDevice(const QString &fileName, const QString &deviceId)
{
    const QString method = u"openFile"_s;

    QDBusMessage msg = QDBusMessage::createMethodCall(u"org.kde.kdeconnect"_s,
                                                      u"/modules/kdeconnect/devices/"_s + deviceId + u"/share"_s,
                                                      u"org.kde.kdeconnect.device.share"_s,
                                                      method);
    msg.setArguments({QUrl::fromLocalFile(fileName).toString()});

    QDBusConnection::sessionBus().send(msg);
}

#include "moc_itinerarykdeconnecthandler.cpp"
