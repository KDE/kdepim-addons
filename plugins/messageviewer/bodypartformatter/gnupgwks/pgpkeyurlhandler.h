/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/BodyPartURLHandler>
// needed for Q_REQUIRED_RESULT
#include <QtGlobal>
class QUrlQuery;

class ApplicationPgpKeyUrlHandler : public MessageViewer::Interface::BodyPartURLHandler
{
public:
    ApplicationPgpKeyUrlHandler() = default;
    QString name() const override;
    bool handleClick(MessageViewer::Viewer *viewerInstance, MimeTreeParser::Interface::BodyPart *part, const QString &path) const override;
    bool handleContextMenuRequest(MimeTreeParser::Interface::BodyPart *part, const QString &path, const QPoint &p) const override;
    QString statusBarMessage(MimeTreeParser::Interface::BodyPart *part, const QString &path) const override;

private:
    Q_REQUIRED_RESULT QUrlQuery decodePath(const QString &path) const;
};
