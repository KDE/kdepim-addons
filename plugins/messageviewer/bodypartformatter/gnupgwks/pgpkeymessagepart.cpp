/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "pgpkeymessagepart.h"

#include <QProcess>

#include <KMime/Content>
#include <MimeTreeParser/BodyPart>

PgpKeyMessagePart::PgpKeyMessagePart(MimeTreeParser::Interface::BodyPart *part)
    : MimeTreeParser::MessagePart(part->objectTreeParser(), QString())
{
    setContent(part->content());
    parseContent(part->content());
}

QDateTime PgpKeyMessagePart::keyDate() const
{
    return mKeyDate;
}

QString PgpKeyMessagePart::keyID() const
{
    return mKeyID;
}

QString PgpKeyMessagePart::userID() const
{
    return mUserID;
}

QString PgpKeyMessagePart::fingerprint() const
{
    return mFingerprint;
}

GpgME::Key PgpKeyMessagePart::key() const
{
    return mKey;
}

void PgpKeyMessagePart::setKey(const GpgME::Key &key)
{
    mKey = key;
}

QString PgpKeyMessagePart::error() const
{
    return mError;
}

void PgpKeyMessagePart::setError(const QString &error)
{
    mError = error;
}

QByteArray PgpKeyMessagePart::rawKey() const
{
    return content()->decodedContent();
}

void PgpKeyMessagePart::setSearchRunning(bool searchRunning)
{
    mSearchRunning = searchRunning;
}

bool PgpKeyMessagePart::searchRunning() const
{
    return mSearchRunning;
}

void PgpKeyMessagePart::parseContent(KMime::Content *node)
{
    // TODO if GpgME dependency is 1.9.0 this can use
    // GpgME::Data::toKeys
    //
    // something like:
    // QGpgME::QByteArrayDataProvider dp(node->decodedContent());
    // Data data(&dp);
    // std::vector <Key> keys = data.toKeys();
    QProcess p;
    p.start(QStringLiteral("gpg"), {QStringLiteral("--with-colons"), QStringLiteral("--fixed-list-mode"), QStringLiteral("--with-fingerprint")});
    p.waitForStarted();
    p.write(node->decodedContent());
    p.closeWriteChannel();
    p.waitForReadyRead();
    const QByteArray result = p.readAllStandardOutput();
    p.waitForFinished();

    const auto lines = result.split('\n');
    for (const auto &line : lines) {
        const auto cols = line.split(':');
        if (cols.isEmpty()) {
            continue;
        }

        const int size = cols.size();

        // "pub" line can appear multiple times, but we are only interested in
        // the first one
        if (cols[0] == "pub" && mKeyID.isEmpty()) {
            if (size > 4) {
                mKeyID = QString::fromUtf8(cols[4]);
            }
            // gpg1: "pub" contains UID
            if (size > 9) {
                mUserID = QString::fromUtf8(cols[9]);
            }
            if (size > 6) {
                mKeyDate = QDateTime::fromSecsSinceEpoch(cols[5].toUInt());
            }
            // gpg2: UID is on a separate line
        } else if (cols[0] == "uid" && size > 9 && mUserID.isEmpty()) {
            mUserID = QString::fromUtf8(cols[9]);
        } else if (cols[0] == "fpr" && size > 9 && mFingerprint.isEmpty()) {
            mFingerprint = QString::fromLatin1(cols[9]);
        }
    }
}

#include "moc_pgpkeymessagepart.cpp"
