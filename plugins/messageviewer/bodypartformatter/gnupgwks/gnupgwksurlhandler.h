/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef GNUPGWKSURLHANDLER_H_
#define GNUPGWKSURLHANDLER_H_

#include <MessageViewer/BodyPartURLHandler>

#include <KMime/Message>

class GnuPGWKSMessagePart;

class ApplicationGnuPGWKSUrlHandler : public MessageViewer::Interface::BodyPartURLHandler
{
public:
    ApplicationGnuPGWKSUrlHandler() = default;

    QString name() const override;
    bool handleClick(MessageViewer::Viewer *viewerInstance, MimeTreeParser::Interface::BodyPart *part, const QString &path) const override;
    bool handleContextMenuRequest(MimeTreeParser::Interface::BodyPart *part, const QString &path, const QPoint &p) const override;
    QString statusBarMessage(MimeTreeParser::Interface::BodyPart *part, const QString &path) const override;

private:
    bool sendConfirmation(MessageViewer::Viewer *viewerInstance, const GnuPGWKSMessagePart &mp) const;

    QByteArray createConfirmation(const KMime::Message::Ptr &msg) const;
};

#endif
