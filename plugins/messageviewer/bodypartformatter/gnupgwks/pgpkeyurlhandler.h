/*
  Copyright (c) 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

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

#ifndef PGPKEYURLHANDLER_H
#define PGPKEYURLHANDLER_H

#include <QtGlobal>
#include <MessageViewer/BodyPartURLHandler>

class QUrlQuery;

class ApplicationPgpKeyUrlHandler : public MimeTreeParser::Interface::BodyPartURLHandler
{
public:
    ApplicationPgpKeyUrlHandler() = default;

    bool handleClick(MessageViewer::Viewer *viewerInstance,
                     MimeTreeParser::Interface::BodyPart *part,
                     const QString &path) const Q_DECL_OVERRIDE;
    bool handleContextMenuRequest(MimeTreeParser::Interface::BodyPart *part,
                                  const QString &path,
                                  const QPoint &p) const Q_DECL_OVERRIDE;
    QString statusBarMessage(MimeTreeParser::Interface::BodyPart *part,
                             const QString &path) const Q_DECL_OVERRIDE;

private:
    QUrlQuery decodePath(const QString &path) const;
};


#endif

