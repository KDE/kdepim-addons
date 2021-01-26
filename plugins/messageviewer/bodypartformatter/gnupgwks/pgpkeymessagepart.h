/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef PGPKEYMESSAGEPART_H_
#define PGPKEYMESSAGEPART_H_

#include <MimeTreeParser/MessagePart>

#include <QDateTime>
#include <QString>

#include <gpgme++/key.h>

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

class PgpKeyMessagePart : public MimeTreeParser::MessagePart
{
    Q_OBJECT
public:
    explicit PgpKeyMessagePart(MimeTreeParser::Interface::BodyPart *part);
    ~PgpKeyMessagePart() = default;

    QDateTime keyDate() const;
    QString userID() const;
    QString keyID() const;
    QString fingerprint() const;

    QString error() const;
    void setError(const QString &error);

    void setKey(const GpgME::Key &key);
    GpgME::Key key() const;

    QByteArray rawKey() const;

    void setSearchRunning(bool searchRunning);
    bool searchRunning() const;

protected:
    void parseContent(KMime::Content *node);

    QDateTime mKeyDate;
    QString mUserID;
    QString mKeyID;
    QString mFingerprint;
    QString mError;
    GpgME::Key mKey;
    bool mSearchRunning = false;
};

#endif
