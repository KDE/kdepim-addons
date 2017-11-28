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

#ifndef SEMANTICURLHANDLER_H
#define SEMANTICURLHANDLER_H

#include <MessageViewer/BodyPartURLHandler>

#include <KCalCore/Event>

#include <QObject>

class SemanticMemento;

/** URL handler for the semantic plugin. */
class SemanticUrlHandler : public QObject, public MessageViewer::Interface::BodyPartURLHandler
{
    Q_OBJECT
public:
    SemanticUrlHandler() = default;
    ~SemanticUrlHandler() = default;

    bool handleClick(MessageViewer::Viewer *viewerInstance, MimeTreeParser::Interface::BodyPart *part, const QString &path) const override;
    bool handleContextMenuRequest(MimeTreeParser::Interface::BodyPart *part, const QString &path, const QPoint &p) const override;
    QString statusBarMessage(MimeTreeParser::Interface::BodyPart *part, const QString &path) const override;

private:
    SemanticMemento *memento(MimeTreeParser::Interface::BodyPart *part) const;
    QDate dateForReservation(SemanticMemento *memento) const;
    void showCalendar(const QDate &date) const;

    KCalCore::Event::Ptr eventForReservation(const QVariant &reservation) const;
    KCalCore::Event::Ptr eventForFlightReservation(const QVariant &reservation) const;
    KCalCore::Event::Ptr eventForLodgingReservation(const QVariant &reservation) const;
    KCalCore::Event::Ptr eventForTrainReservation(const QVariant &reservation) const;
    void addToCalendar(SemanticMemento *memento) const;
};

#endif // SEMANTICURLHANDLER_H
