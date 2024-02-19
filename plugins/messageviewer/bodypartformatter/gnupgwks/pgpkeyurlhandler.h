/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/BodyPartURLHandler>
class QUrlQuery;

class ApplicationPgpKeyUrlHandler : public MessageViewer::Interface::BodyPartURLHandler
{
public:
    ApplicationPgpKeyUrlHandler() = default;
    [[nodiscard]] QString name() const override;
    bool handleClick(MessageViewer::Viewer *viewerInstance, MimeTreeParser::Interface::BodyPart *part, const QString &path) const override;
    bool handleContextMenuRequest(MimeTreeParser::Interface::BodyPart *part, const QString &path, const QPoint &p) const override;
    [[nodiscard]] QString statusBarMessage(MimeTreeParser::Interface::BodyPart *part, const QString &path) const override;

private:
    [[nodiscard]] QUrlQuery decodePath(const QString &path) const;
};
