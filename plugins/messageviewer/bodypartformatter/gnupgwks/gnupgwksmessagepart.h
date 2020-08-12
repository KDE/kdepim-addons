/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef GNUPGWKSMESSAGEPART_H_
#define GNUPGWKSMESSAGEPART_H_

#include <MimeTreeParser/MessagePart>

#include <QString>

namespace MimeTreeParser {
namespace Interface {
class BodyPart;
}
}

namespace KMime {
class Content;
}

class GnuPGWKSMessagePart : public MimeTreeParser::MessagePart
{
    Q_OBJECT
public:
    enum ConfirmationType {
        UnknownType,
        ConfirmationRequest,
        ConfirmationResponse
    };

    explicit GnuPGWKSMessagePart(MimeTreeParser::Interface::BodyPart *part);

    virtual ~GnuPGWKSMessagePart() = default;

    ConfirmationType confirmationType() const;
    QString sender() const;
    QString address() const;
    QString fingerprint() const;
    QString nonce() const;

protected:
    void parseContent(KMime::Content *node);
    ConfirmationType stringToType(const QStringRef &str);

    QString mSender;
    QString mAddress;
    QString mFingerprint;
    QString mNonce;
    ConfirmationType mType = UnknownType;
};

#endif
