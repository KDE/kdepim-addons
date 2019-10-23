/*
   Copyright (c) 2017 Volker Krause <vkrause@kde.org>

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

#ifndef ITINERARYKDECONNECTHANDLER_H
#define ITINERARYKDECONNECTHANDLER_H

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

    QVector<Device> devices() const;

    void sendToDevice(const QString &fileName, const QString &deviceId);
};

#endif // ITINERARYKDECONNECTHANDLER_H
