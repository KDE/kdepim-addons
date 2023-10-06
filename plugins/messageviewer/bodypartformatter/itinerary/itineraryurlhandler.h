/*
   SPDX-FileCopyrightText: 2017 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/BodyPartURLHandler>

#include <QObject>

class ItineraryMemento;
class ItineraryKDEConnectHandler;

/** URL handler for the itinerary plugin. */
class ItineraryUrlHandler : public QObject, public MessageViewer::Interface::BodyPartURLHandler
{
    Q_OBJECT
public:
    ~ItineraryUrlHandler() override = default;
    void setKDEConnectHandler(ItineraryKDEConnectHandler *kdeConnect);

    QString name() const override;
    bool handleClick(MessageViewer::Viewer *viewerInstance, MimeTreeParser::Interface::BodyPart *part, const QString &path) const override;
    bool handleContextMenuRequest(MimeTreeParser::Interface::BodyPart *part, const QString &path, const QPoint &p) const override;
    QString statusBarMessage(MimeTreeParser::Interface::BodyPart *part, const QString &path) const override;

    [[nodiscard]] static bool hasItineraryApp();

private:
    ItineraryMemento *memento(MimeTreeParser::Interface::BodyPart *part) const;
    void showCalendar(QDate date) const;
    void addToCalendar(ItineraryMemento *memento) const;
    void openInApp(MimeTreeParser::Interface::BodyPart *part) const;
    void openWithKDEConnect(MimeTreeParser::Interface::BodyPart *part, const QString &deviceId) const;
    [[nodiscard]] QString createItineraryFile(MimeTreeParser::Interface::BodyPart *part) const;

    ItineraryKDEConnectHandler *m_kdeConnect = nullptr;
};
