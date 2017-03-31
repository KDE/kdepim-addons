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

#ifndef GNUPGWKSFORMATTER_H_
#define GNUPGWKSFORMATTER_H_

#include <MimeTreeParser/BodyPartFormatter>

class GnuPGWKSMessagePart;
class GnuPGWKSMemento;

class ApplicationGnuPGWKSFormatter : public MimeTreeParser::Interface::BodyPartFormatter
{
public:
    ApplicationGnuPGWKSFormatter() = default;

    MimeTreeParser::Interface::MessagePart::Ptr process(MimeTreeParser::Interface::BodyPart &part) const Q_DECL_OVERRIDE;

    MimeTreeParser::Interface::BodyPartFormatter::Result format(MimeTreeParser::Interface::BodyPart *part,
            MimeTreeParser::HtmlWriter *writer) const Q_DECL_OVERRIDE;
    MimeTreeParser::Interface::BodyPartFormatter::Result format(MimeTreeParser::Interface::BodyPart *part,
            MimeTreeParser::HtmlWriter *writer,
            QObject *asyncResultObserver) const Q_DECL_OVERRIDE;

private:
    enum WKSStatus {
        CheckingPublishing,
        NotPublished,
        Published
    };

    QString render(const GnuPGWKSMessagePart &mp, WKSStatus status) const;
    WKSStatus runMemento(GnuPGWKSMemento *memento, const GnuPGWKSMessagePart &mp, bool async) const;
};

#endif
