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

#ifndef ITINERARYURLHANDLER_H
#define ITINERARYURLHANDLER_H

#include <MessageViewer/BodyPartURLHandler>

#include <QObject>

class ItineraryMemento;

/** URL handler for the itinerary plugin. */
class ItineraryUrlHandler : public QObject, public MessageViewer::Interface::BodyPartURLHandler
{
    Q_OBJECT
public:
    ItineraryUrlHandler();
    ~ItineraryUrlHandler() override = default;

    QString name() const override;
    bool handleClick(MessageViewer::Viewer *viewerInstance, MimeTreeParser::Interface::BodyPart *part, const QString &path) const override;
    bool handleContextMenuRequest(MimeTreeParser::Interface::BodyPart *part, const QString &path, const QPoint &p) const override;
    QString statusBarMessage(MimeTreeParser::Interface::BodyPart *part, const QString &path) const override;

    static bool hasItineraryApp();
private:
    ItineraryMemento *memento(MimeTreeParser::Interface::BodyPart *part) const;
    void showCalendar(const QDate &date) const;
    void addToCalendar(ItineraryMemento *memento) const;
    void openInApp(MimeTreeParser::Interface::BodyPart *part) const;
    void openWithKDEConnect(MimeTreeParser::Interface::BodyPart *part, const QString &deviceId) const;
    QString createItineraryFile(MimeTreeParser::Interface::BodyPart *part) const;

    static QString m_appPath;
};

#endif // ITINERARYURLHANDLER_H
