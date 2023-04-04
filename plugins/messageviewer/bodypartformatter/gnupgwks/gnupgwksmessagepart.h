/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <MimeTreeParser/MessagePart>

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

class GnuPGWKSMessagePart : public MimeTreeParser::MessagePart
{
    Q_OBJECT
public:
    enum ConfirmationType {
        UnknownType,
        ConfirmationRequest,
        ConfirmationResponse,
    };

    explicit GnuPGWKSMessagePart(MimeTreeParser::Interface::BodyPart *part);

    ~GnuPGWKSMessagePart() override = default;

    Q_REQUIRED_RESULT ConfirmationType confirmationType() const;
    Q_REQUIRED_RESULT QString sender() const;
    Q_REQUIRED_RESULT QString address() const;
    Q_REQUIRED_RESULT QString fingerprint() const;
    Q_REQUIRED_RESULT QString nonce() const;

protected:
    void parseContent(KMime::Content *node);
    Q_REQUIRED_RESULT ConfirmationType stringToType(const QStringView &str);
    QString mSender;
    QString mAddress;
    QString mFingerprint;
    QString mNonce;
    ConfirmationType mType = UnknownType;
};
