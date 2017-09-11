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

#ifndef PGPKEYMESSAGEPART_H_
#define PGPKEYMESSAGEPART_H_

#include <QDateTime>
#include <QString>

#include <gpgme++/key.h>

namespace MimeTreeParser {
namespace Interface {
class BodyPart;
class ObjectTreeSource;
}
}
namespace KMime {
class Content;
}

class PgpKeyMessagePart
{
public:
    PgpKeyMessagePart(MimeTreeParser::Interface::BodyPart *part);

    virtual ~PgpKeyMessagePart() = default;

    QDateTime keyDate() const;
    QString userID() const;
    QString keyID() const;
    QString fingerprint() const;

    QString error() const;
    void setError(const QString &error);

    void setKey(const GpgME::Key &key);
    GpgME::Key key() const;

    QByteArray rawKey() const;

    MimeTreeParser::Interface::ObjectTreeSource *source() const;
    MimeTreeParser::Interface::BodyPart *part() const;

protected:
    void parseContent(KMime::Content *node);

    MimeTreeParser::Interface::BodyPart *mPart = nullptr;
    QDateTime mKeyDate;
    QString mUserID;
    QString mKeyID;
    QString mFingerprint;
    QString mError;
    GpgME::Key mKey;
};

#endif
