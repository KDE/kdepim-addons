/*
   SPDX-FileCopyrightText: 2017 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>
#include <QString>

class ItineraryKDEConnectHandler : public QObject
{
    Q_OBJECT
public:
    explicit ItineraryKDEConnectHandler(QObject *parent = nullptr);

    struct Device {
        QString deviceId;
        QString name;
    };

    [[nodiscard]] QList<Device> devices() const;

    void sendToDevice(const QString &fileName, const QString &deviceId);
};
