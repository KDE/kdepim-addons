/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternalscriptparseargument.h"
ViewerPluginExternalScriptParseArgument::ViewerPluginExternalScriptParseArgument() = default;

void ViewerPluginExternalScriptParseArgument::setMessage(const KMime::Message::Ptr &msg)
{
    mMessage = msg;
}

void ViewerPluginExternalScriptParseArgument::setAkonadiUrl(const QString &akonadiUrl)
{
    mAkonadiUrl = akonadiUrl;
}

QStringList ViewerPluginExternalScriptParseArgument::parse(const QStringList &scriptArguments)
{
    if (mMessage.isNull()) {
        return scriptArguments;
    }

    QStringList newArguments;
    newArguments.reserve(scriptArguments.count());
    for (const QString &arg : scriptArguments) {
        if (arg == QLatin1StringView("%s")) {
            const KMime::Headers::Subject *const subject = mMessage ? mMessage->subject(false) : nullptr;
            newArguments << QStringLiteral("\"%1\"").arg(subject ? subject->asUnicodeString() : QString());
        } else if (arg == QLatin1StringView("%from")) {
            const KMime::Headers::From *const from = mMessage ? mMessage->from(false) : nullptr;
            newArguments << QStringLiteral("\"%1\"").arg(from ? from->asUnicodeString() : QString());
        } else if (arg == QLatin1StringView("%to")) {
            const KMime::Headers::To *const to = mMessage ? mMessage->to(false) : nullptr;
            newArguments << QStringLiteral("\"%1\"").arg(to ? to->asUnicodeString() : QString());
        } else if (arg == QLatin1StringView("%cc")) {
            const KMime::Headers::Cc *const cc = mMessage ? mMessage->cc(false) : nullptr;
            newArguments << QStringLiteral("\"%1\"").arg(cc ? cc->asUnicodeString() : QString());
        } else if (arg == QLatin1StringView("%bcc")) {
            const KMime::Headers::Bcc *const bcc = mMessage ? mMessage->bcc(false) : nullptr;
            newArguments << QStringLiteral("\"%1\"").arg(bcc ? bcc->asUnicodeString() : QString());
        } else if (arg == QLatin1StringView("%body")) {
            const QByteArray body = mMessage ? mMessage->body() : nullptr;
            newArguments << QStringLiteral("\"%1\"").arg(QLatin1StringView(body));
        } else if (arg == QLatin1StringView("%inreplyto")) {
            KMime::Headers::InReplyTo *inReplyTo = mMessage ? mMessage->inReplyTo(false) : nullptr;
            newArguments << QStringLiteral("\"%1\"").arg(inReplyTo ? inReplyTo->asUnicodeString() : QString());
        } else if (arg == QLatin1StringView("%akonadiUrl")) {
            newArguments << mAkonadiUrl;
        } else {
            newArguments << arg;
        }
    }
    return newArguments;
}
