/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "gnupgwksmessagepart.h"

#include <KMime/Content>
#include <MimeTreeParser/BodyPart>
using namespace Qt::Literals::StringLiterals;

GnuPGWKSMessagePart::GnuPGWKSMessagePart(MimeTreeParser::Interface::BodyPart *part)
    : MimeTreeParser::MessagePart(part->objectTreeParser(), QString())
{
    setContent(part->content());
    parseContent(content());
}

GnuPGWKSMessagePart::ConfirmationType GnuPGWKSMessagePart::confirmationType() const
{
    return mType;
}

QString GnuPGWKSMessagePart::address() const
{
    return mAddress;
}

QString GnuPGWKSMessagePart::sender() const
{
    return mSender;
}

QString GnuPGWKSMessagePart::fingerprint() const
{
    return mFingerprint;
}

QString GnuPGWKSMessagePart::nonce() const
{
    return mNonce;
}

GnuPGWKSMessagePart::ConfirmationType GnuPGWKSMessagePart::stringToType(const QStringView &str)
{
    if (str == "confirmation-request"_L1) {
        return ConfirmationRequest;
    } else if (str == "confirmation-response"_L1) {
        return ConfirmationResponse;
    } else {
        return UnknownType;
    }
}

void GnuPGWKSMessagePart::parseContent(KMime::Content *node)
{
    const auto text = QString::fromUtf8(node->decodedBody());
    const auto lines = text.split(u'\n', Qt::SkipEmptyParts);
    // https://tools.ietf.org/id/draft-koch-openpgp-webkey-service-02.txt
    // sections 4.3 and 4.4
    for (const auto &line : lines) {
        if (line.startsWith("type:"_L1)) {
            mType = stringToType(QStringView(line).mid(sizeof("type:") - 1).trimmed());
        } else if (line.startsWith("sender:"_L1)) {
            mSender = QStringView(line).mid(sizeof("sender:") - 1).trimmed().toString();
        } else if (line.startsWith("address:"_L1)) {
            mAddress = QStringView(line).mid(sizeof("address:") - 1).trimmed().toString();
        } else if (line.startsWith("fingerprint:"_L1)) {
            mFingerprint = QStringView(line).mid(sizeof("fingerprint:") - 1).trimmed().toString();
        } else if (line.startsWith("nonce:"_L1)) {
            mNonce = QStringView(line).mid(sizeof("nonce:") - 1).trimmed().toString();
        }
    }
}

#include "moc_gnupgwksmessagepart.cpp"
