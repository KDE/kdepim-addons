/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternalscriptparseargument.h"
#include <QTextDocument>
using namespace Qt::Literals::StringLiterals;

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
        if (arg == "%s"_L1) {
            const KMime::Headers::Subject *const subject = mMessage->subject(KMime::CreatePolicy::DontCreate);
            newArguments << u"\"%1\""_s.arg(subject ? subject->asUnicodeString() : QString());
        } else if (arg == "%from"_L1) {
            const KMime::Headers::From *const from = mMessage->from(KMime::CreatePolicy::DontCreate);
            newArguments << u"\"%1\""_s.arg(from ? from->asUnicodeString() : QString());
        } else if (arg == "%to"_L1) {
            const KMime::Headers::To *const to = mMessage->to(KMime::CreatePolicy::DontCreate);
            newArguments << u"\"%1\""_s.arg(to ? to->asUnicodeString() : QString());
        } else if (arg == "%cc"_L1) {
            const KMime::Headers::Cc *const cc = mMessage->cc(KMime::CreatePolicy::DontCreate);
            newArguments << u"\"%1\""_s.arg(cc ? cc->asUnicodeString() : QString());
        } else if (arg == "%bcc"_L1) {
            const KMime::Headers::Bcc *const bcc = mMessage->bcc(KMime::CreatePolicy::DontCreate);
            newArguments << u"\"%1\""_s.arg(bcc ? bcc->asUnicodeString() : QString());
        } else if (arg == "%body"_L1) {
            // const QByteArray body = mMessage->body();
            // qDebug() << " BODY ************" << mMessage->encodedBody();
            QTextDocument doc;
            doc.setHtml(mMessage->decodedText());
            // qDebug() << " AFTYER BODY ************" << doc.toPlainText();
            newArguments << u"\"%1\""_s.arg(doc.toPlainText());
        } else if (arg == "%inreplyto"_L1) {
            KMime::Headers::InReplyTo *inReplyTo = mMessage->inReplyTo(KMime::CreatePolicy::DontCreate);
            newArguments << u"\"%1\""_s.arg(inReplyTo ? inReplyTo->asUnicodeString() : QString());
        } else if (arg == "%akonadiUrl"_L1) {
            newArguments << mAkonadiUrl;
        } else {
            newArguments << arg;
        }
    }
    return newArguments;
}
