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

    [[nodiscard]] QDateTime keyDate() const;
    [[nodiscard]] QString userID() const;
    [[nodiscard]] QString keyID() const;
    [[nodiscard]] QString fingerprint() const;

    [[nodiscard]] QString error() const;
    void setError(const QString &error);

    void setKey(const GpgME::Key &key);
    [[nodiscard]] GpgME::Key key() const;

    [[nodiscard]] QByteArray rawKey() const;

    void setSearchRunning(bool searchRunning);
    [[nodiscard]] bool searchRunning() const;

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
