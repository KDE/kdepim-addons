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

    [[nodiscard]] ConfirmationType confirmationType() const;
    [[nodiscard]] QString sender() const;
    [[nodiscard]] QString address() const;
    [[nodiscard]] QString fingerprint() const;
    [[nodiscard]] QString nonce() const;

protected:
    void parseContent(KMime::Content *node);
    [[nodiscard]] ConfirmationType stringToType(const QStringView &str);
    QString mSender;
    QString mAddress;
    QString mFingerprint;
    QString mNonce;
    ConfirmationType mType = UnknownType;
};
