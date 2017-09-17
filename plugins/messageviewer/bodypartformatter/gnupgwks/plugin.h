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

#ifndef GNUPGWKSPLUGIN_H
#define GNUPGWKSPLUGIN_H

#include <MimeTreeParser/BodyPartFormatter>

class ApplicationGnuPGWKSPlugin : public QObject, public MimeTreeParser::Interface::BodyPartFormatterPlugin
{
    Q_OBJECT
    Q_INTERFACES(MimeTreeParser::Interface::BodyPartFormatterPlugin)
    Q_PLUGIN_METADATA(IID "com.kde.messageviewer.bodypartformatter")
public:
    ApplicationGnuPGWKSPlugin() = default;

    const MimeTreeParser::Interface::BodyPartFormatter *bodyPartFormatter(int idx) const override;
    const char *subtype(int idx) const override;
    const char *type(int idx) const override;
    const MimeTreeParser::Interface::BodyPartURLHandler *urlHandler(int idx) const override;
};

#endif
