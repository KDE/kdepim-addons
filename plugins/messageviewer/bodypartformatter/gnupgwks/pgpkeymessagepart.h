/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

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
    ~PgpKeyMessagePart() override = default;

    Q_REQUIRED_RESULT QDateTime keyDate() const;
    Q_REQUIRED_RESULT QString userID() const;
    Q_REQUIRED_RESULT QString keyID() const;
    Q_REQUIRED_RESULT QString fingerprint() const;

    Q_REQUIRED_RESULT QString error() const;
    void setError(const QString &error);

    void setKey(const GpgME::Key &key);
    Q_REQUIRED_RESULT GpgME::Key key() const;

    Q_REQUIRED_RESULT QByteArray rawKey() const;

    void setSearchRunning(bool searchRunning);
    Q_REQUIRED_RESULT bool searchRunning() const;

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
