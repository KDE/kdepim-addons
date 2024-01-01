/*  -*- c++ -*-
    messageviewer/headerstyle.h

    This file is part of KMail, the KDE mail client.
    SPDX-FileCopyrightText: 2003 Marc Mutz <mutz@kde.org>
    SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: GPL-2.0-only
*/

#include "briefheaderstyle.h"
#include <MessageViewer/HeaderStrategy>
#include <MessageViewer/MessageViewerSettings>

#include <MessageCore/StringUtil>

#include <KLocalizedString>

#include <QApplication>
#include <QRegularExpression>

using namespace MessageCore;
using namespace MessageViewer;
//
// BriefHeaderStyle
//   Show everything in a single line, don't show header field names.
//

QString BriefHeaderStyle::format(KMime::Message *message) const
{
    if (!message) {
        return {};
    }

    const HeaderStrategy *strategy = headerStrategy();
    // The direction of the header is determined according to the direction
    // of the application layout.

    const QString dir = QApplication::isRightToLeft() ? QStringLiteral("rtl") : QStringLiteral("ltr");

    // However, the direction of the message subject within the header is
    // determined according to the contents of the subject itself. Since
    // the "Re:" and "Fwd:" prefixes would always cause the subject to be
    // considered left-to-right, they are ignored when determining its
    // direction.

    const QString subjectDir = mHeaderStyleUtil.subjectDirectionString(message);

    QString headerStr = QLatin1String(R"(<div class="header" dir=")") + dir + QLatin1String("\">\n");

    if (strategy->showHeader(QStringLiteral("subject"))) {
        const KTextToHTML::Options flags = KTextToHTML::PreserveSpaces | KTextToHTML::ReplaceSmileys;

        headerStr += QLatin1String("<div dir=\"") + subjectDir + QLatin1String("\">\n") + QStringLiteral("<b style=\"font-size:130%\">");

        headerStr += mHeaderStyleUtil.subjectString(message, flags) + QStringLiteral("</b></div>\n");
    }
    QStringList headerParts;

    if (strategy->showHeader(QStringLiteral("from"))) {
        /*TODO(Andras) review if it can happen or not
        if ( fromStr.isEmpty() ) // no valid email in from, maybe just a name
        fromStr = message->fromStrip(); // let's use that
        */
        QString fromPart = StringUtil::emailAddrAsAnchor(message->from(), StringUtil::DisplayFullAddress);
        if (!vCardName().isEmpty()) {
            fromPart += QLatin1String("&nbsp;&nbsp;<a href=\"") + vCardName() + QLatin1String("\">") + i18n("[vCard]") + QLatin1String("</a>");
        }
        headerParts << fromPart;
    }

    if (strategy->showHeader(QStringLiteral("cc")) && message->cc(false)) {
        const QString str = StringUtil::emailAddrAsAnchor(message->cc(), StringUtil::DisplayFullAddress);
        if (!str.isEmpty()) {
            headerParts << i18n("CC: ") + str;
        }
    }

    if (strategy->showHeader(QStringLiteral("bcc")) && message->bcc(false)) {
        const QString str = StringUtil::emailAddrAsAnchor(message->bcc(), StringUtil::DisplayFullAddress);
        if (!str.isEmpty()) {
            headerParts << i18n("BCC: ") + str;
        }
    }

    if (strategy->showHeader(QStringLiteral("date"))) {
        headerParts << mHeaderStyleUtil.strToHtml(HeaderStyleUtil::dateString(message, /* shortDate = */ MessageViewer::HeaderStyleUtil::ShortDate));
    }

    // remove all empty (modulo whitespace) entries and joins them via ", \n"
    headerStr += QLatin1String(" (") + headerParts.filter(QRegularExpression(QStringLiteral("\\S"))).join(QLatin1String(",\n")) + QLatin1Char(')');

    headerStr += QLatin1String("</div>\n");

    // ### iterate over the rest of strategy->headerToDisplay() (or
    // ### all headers if DefaultPolicy == Display) (elsewhere, too)
    return headerStr;
}
