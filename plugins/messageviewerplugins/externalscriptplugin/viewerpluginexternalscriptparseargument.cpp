/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "viewerpluginexternalscriptparseargument.h"

ViewerPluginExternalScriptParseArgument::ViewerPluginExternalScriptParseArgument()
{

}

void ViewerPluginExternalScriptParseArgument::setMessage(const KMime::Message::Ptr &msg)
{
    mMessage = msg;
}

QStringList ViewerPluginExternalScriptParseArgument::parse(const QStringList &scriptArguments)
{
    if (mMessage.isNull()) {
        return scriptArguments;
    }

    QStringList newArguments;
    Q_FOREACH(const QString &arg, scriptArguments) {
        if (arg == QString::fromLatin1("%s")) {
            const KMime::Headers::Subject *const subject = mMessage ? mMessage->subject(false) : Q_NULLPTR;
            newArguments << QStringLiteral("\"%1\"").arg(subject ? subject->asUnicodeString() : QString());  
        } else if (arg == QString::fromLatin1("%from")) {
            const KMime::Headers::From *const from = mMessage ? mMessage->from(false) : Q_NULLPTR;
            newArguments << QStringLiteral("\"%1\"").arg(from ? from->asUnicodeString() : QString());
        } else if (arg == QString::fromLatin1("%to")) {
            const KMime::Headers::To *const to = mMessage ? mMessage->to(false) : Q_NULLPTR;
            newArguments << QStringLiteral("\"%1\"").arg(to ? to->asUnicodeString() : QString());
        } else if (arg == QString::fromLatin1("%cc")) {
            const KMime::Headers::Cc *const cc = mMessage ? mMessage->cc(false) : Q_NULLPTR;
            newArguments << QStringLiteral("\"%1\"").arg(cc ? cc->asUnicodeString() : QString());
        } else if (arg == QString::fromLatin1("%body")) {
            const QByteArray body = mMessage ? mMessage->body() : Q_NULLPTR;
            newArguments << QStringLiteral("\"%1\"").arg(QLatin1String(body));
        } else {
            newArguments << arg;
        }
    }

    //TODO add more arguments
    return newArguments;
}
