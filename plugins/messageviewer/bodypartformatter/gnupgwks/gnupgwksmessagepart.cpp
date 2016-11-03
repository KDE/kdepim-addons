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

#include "gnupgwksmessagepart.h"

#include <MimeTreeParser/BodyPart>
#include <KMime/Content>


GnuPGWKSMessagePart::GnuPGWKSMessagePart(MimeTreeParser::Interface::BodyPart *part)
    : mPart(part)
    , mType(UnknownType)
{
    parseContent(part->content());
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

KMime::Content *GnuPGWKSMessagePart::node() const
{
    return mPart->content();
}

MimeTreeParser::Interface::BodyPart *GnuPGWKSMessagePart::part() const
{
    return mPart;
}

GnuPGWKSMessagePart::ConfirmationType GnuPGWKSMessagePart::stringToType(const QStringRef &str)
{
    if (str == QLatin1String("confirmation-request")) {
        return ConfirmationRequest;
    } else if (str == QLatin1String("confirmation-response")) {
        return ConfirmationResponse;
    } else {
        return UnknownType;
    }
}

void GnuPGWKSMessagePart::parseContent(KMime::Content *node)
{
    const auto text = QString::fromUtf8(node->decodedContent());
    const auto lines = text.split(QLatin1Char('\n'), QString::SkipEmptyParts);
    // https://tools.ietf.org/id/draft-koch-openpgp-webkey-service-02.txt
    // sections 4.3 and 4.4
    for (const auto &line : lines) {
        if (line.startsWith(QLatin1String("type:"))) {
            mType = stringToType(line.midRef(sizeof("type:") - 1).trimmed());
        } else if (line.startsWith(QLatin1String("sender:"))) {
            mSender = line.midRef(sizeof("sender:") - 1).trimmed().toString();
        } else if (line.startsWith(QLatin1String("address:"))) {
            mAddress = line.midRef(sizeof("address:") - 1).trimmed().toString();
        } else if (line.startsWith(QLatin1String("fingerprint:"))) {
            mFingerprint = line.midRef(sizeof("fingerprint:") - 1).trimmed().toString();
        } else if (line.startsWith(QLatin1String("nonce:"))) {
            mNonce = line.midRef(sizeof("nonce:") - 1).trimmed().toString();
        }
    }
}
