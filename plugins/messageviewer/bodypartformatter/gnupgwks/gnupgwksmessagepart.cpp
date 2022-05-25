/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "gnupgwksmessagepart.h"

#include <KMime/Content>
#include <MimeTreeParser/BodyPart>

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

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
GnuPGWKSMessagePart::ConfirmationType GnuPGWKSMessagePart::stringToType(const QStringRef &str)
#else
GnuPGWKSMessagePart::ConfirmationType GnuPGWKSMessagePart::stringToType(const QStringView &str)
#endif
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
    const auto lines = text.split(QLatin1Char('\n'), Qt::SkipEmptyParts);
    // https://tools.ietf.org/id/draft-koch-openpgp-webkey-service-02.txt
    // sections 4.3 and 4.4
    for (const auto &line : lines) {
        if (line.startsWith(QLatin1String("type:"))) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            mType = stringToType(line.midRef(sizeof("type:") - 1).trimmed());
#else
            mType = stringToType(QStringView(line).mid(sizeof("type:") - 1).trimmed());
#endif
        } else if (line.startsWith(QLatin1String("sender:"))) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            mSender = line.midRef(sizeof("sender:") - 1).trimmed().toString();
#else
            mSender = QStringView(line).mid(sizeof("sender:") - 1).trimmed().toString();
#endif
        } else if (line.startsWith(QLatin1String("address:"))) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            mAddress = line.midRef(sizeof("address:") - 1).trimmed().toString();
#else
            mAddress = QStringView(line).mid(sizeof("address:") - 1).trimmed().toString();
#endif
        } else if (line.startsWith(QLatin1String("fingerprint:"))) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            mFingerprint = line.midRef(sizeof("fingerprint:") - 1).trimmed().toString();
#else
            mFingerprint = QStringView(line).mid(sizeof("fingerprint:") - 1).trimmed().toString();
#endif
        } else if (line.startsWith(QLatin1String("nonce:"))) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            mNonce = line.midRef(sizeof("nonce:") - 1).trimmed().toString();
#else
            mNonce = QStringView(line).mid(sizeof("nonce:") - 1).trimmed().toString();
#endif
        }
    }
}
