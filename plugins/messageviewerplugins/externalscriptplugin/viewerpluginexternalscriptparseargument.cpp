/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternalscriptparseargument.h"
#include <QTextDocument>

ViewerPluginExternalScriptParseArgument::ViewerPluginExternalScriptParseArgument() = default;

void ViewerPluginExternalScriptParseArgument::setMessage(const std::shared_ptr<KMime::Message> &msg)
{
    mMessage = msg;
}

void ViewerPluginExternalScriptParseArgument::setAkonadiUrl(const QString &akonadiUrl)
{
    mAkonadiUrl = akonadiUrl;
}

QStringList ViewerPluginExternalScriptParseArgument::parse(const QStringList &scriptArguments)
{
    if (mMessage == nullptr) {
        return scriptArguments;
    }

    QStringList newArguments;
    newArguments.reserve(scriptArguments.count());
    for (const QString &arg : scriptArguments) {
        if (arg == QLatin1StringView("%s")) {
            const KMime::Headers::Subject *const subject = mMessage->subject(KMime::CreatePolicy::DontCreate);
            newArguments << QStringLiteral("\"%1\"").arg(subject ? subject->asUnicodeString() : QString());
        } else if (arg == QLatin1StringView("%from")) {
            const KMime::Headers::From *const from = mMessage->from(KMime::CreatePolicy::DontCreate);
            newArguments << QStringLiteral("\"%1\"").arg(from ? from->asUnicodeString() : QString());
        } else if (arg == QLatin1StringView("%to")) {
            const KMime::Headers::To *const to = mMessage->to(KMime::CreatePolicy::DontCreate);
            newArguments << QStringLiteral("\"%1\"").arg(to ? to->asUnicodeString() : QString());
        } else if (arg == QLatin1StringView("%cc")) {
            const KMime::Headers::Cc *const cc = mMessage->cc(KMime::CreatePolicy::DontCreate);
            newArguments << QStringLiteral("\"%1\"").arg(cc ? cc->asUnicodeString() : QString());
        } else if (arg == QLatin1StringView("%bcc")) {
            const KMime::Headers::Bcc *const bcc = mMessage->bcc(KMime::CreatePolicy::DontCreate);
            newArguments << QStringLiteral("\"%1\"").arg(bcc ? bcc->asUnicodeString() : QString());
        } else if (arg == QLatin1StringView("%body")) {
            // const QByteArray body = mMessage->body();
            // qDebug() << " BODY ************" << mMessage->encodedBody();
            QTextDocument doc;
            doc.setHtml(QString::fromLatin1(mMessage->encodedBody()));
            // qDebug() << " AFTYER BODY ************" << doc.toPlainText();
            newArguments << QStringLiteral("\"%1\"").arg(doc.toPlainText());
        } else if (arg == QLatin1StringView("%inreplyto")) {
            KMime::Headers::InReplyTo *inReplyTo = mMessage->inReplyTo(KMime::CreatePolicy::DontCreate);
            newArguments << QStringLiteral("\"%1\"").arg(inReplyTo ? inReplyTo->asUnicodeString() : QString());
        } else if (arg == QLatin1StringView("%akonadiUrl")) {
            newArguments << mAkonadiUrl;
        } else {
            newArguments << arg;
        }
    }
    return newArguments;
}
