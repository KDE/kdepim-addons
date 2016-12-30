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

#ifndef GNUPGWKSMESSAGEPART_H_
#define GNUPGWKSMESSAGEPART_H_

#include <QString>

namespace MimeTreeParser
{
namespace Interface
{
class BodyPart;
}
}

namespace KMime
{
class Content;
}

class GnuPGWKSMessagePart
{
public:
    enum ConfirmationType {
        UnknownType,
        ConfirmationRequest,
        ConfirmationResponse
    };

    GnuPGWKSMessagePart(MimeTreeParser::Interface::BodyPart *part);

    virtual ~GnuPGWKSMessagePart() = default;

    ConfirmationType confirmationType() const;
    QString sender() const;
    QString address() const;
    QString fingerprint() const;
    QString nonce() const;
    KMime::Content *node() const;
    MimeTreeParser::Interface::BodyPart *part() const;

protected:
    void parseContent(KMime::Content *node);
    ConfirmationType stringToType(const QStringRef &str);

    MimeTreeParser::Interface::BodyPart *mPart;
    QString mSender;
    QString mAddress;
    QString mFingerprint;
    QString mNonce;
    ConfirmationType mType;
};

#endif
