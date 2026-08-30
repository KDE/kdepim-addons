/*  -*- c++ -*-
    messageviewer/headerstyle.h

    This file is part of KMail, the KDE mail client.
    SPDX-FileCopyrightText: 2003 Marc Mutz <mutz@kde.org>
    SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: GPL-2.0-only
*/

#include "briefheaderstyle.h"
#include <MessageViewer/HeaderStrategy>
#include <MessageViewer/MessageViewerSettings>

#include <MessageCore/StringUtil>

#include <KLocalizedString>

#include <QApplication>
#include <QRegularExpression>
using namespace Qt::Literals::StringLiterals;

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

    const QString dir = QApplication::isRightToLeft() ? u"rtl"_s : u"ltr"_s;

    // However, the direction of the message subject within the header is
    // determined according to the contents of the subject itself. Since
    // the "Re:" and "Fwd:" prefixes would always cause the subject to be
    // considered left-to-right, they are ignored when determining its
    // direction.

    const QString subjectDir = mHeaderStyleUtil.subjectDirectionString(message);

    QString headerStr = R"(<div class="header" dir=")"_L1 + dir + "\">\n"_L1;

    if (strategy->showHeader(u"subject"_s)) {
        const KTextToHTML::Options flags = KTextToHTML::PreserveSpaces | KTextToHTML::ReplaceSmileys;

        headerStr += "<div dir=\""_L1 + subjectDir + "\">\n"_L1 + u"<b style=\"font-size:130%\">"_s;

        headerStr += mHeaderStyleUtil.subjectString(message, flags) + u"</b></div>\n"_s;
    }
    QStringList headerParts;

    if (strategy->showHeader(u"from"_s)) {
        /*TODO(Andras) review if it can happen or not
        if ( fromStr.isEmpty() ) // no valid email in from, maybe just a name
        fromStr = message->fromStrip(); // let's use that
        */
        QString fromPart = StringUtil::emailAddrAsAnchor(message->from(), StringUtil::DisplayFullAddress);
        if (!vCardName().isEmpty()) {
            fromPart += "&nbsp;&nbsp;<a href=\""_L1 + vCardName() + "\">"_L1 + i18n("[vCard]") + "</a>"_L1;
        }
        headerParts << fromPart;
    }

    if (strategy->showHeader(u"cc"_s) && message->cc(KMime::CreatePolicy::DontCreate)) {
        const QString str = StringUtil::emailAddrAsAnchor(message->cc(), StringUtil::DisplayFullAddress);
        if (!str.isEmpty()) {
            headerParts << i18n("CC: ") + str;
        }
    }

    if (strategy->showHeader(u"bcc"_s) && message->bcc(KMime::CreatePolicy::DontCreate)) {
        const QString str = StringUtil::emailAddrAsAnchor(message->bcc(), StringUtil::DisplayFullAddress);
        if (!str.isEmpty()) {
            headerParts << i18n("BCC: ") + str;
        }
    }

    if (strategy->showHeader(u"date"_s)) {
        headerParts << mHeaderStyleUtil.strToHtml(HeaderStyleUtil::dateString(message, /* shortDate = */ MessageViewer::HeaderStyleUtil::ShortDate));
    }

    // remove all empty (modulo whitespace) entries and joins them via ", \n"
    headerStr += " ("_L1 + headerParts.filter(QRegularExpression(u"\\S"_s)).join(",\n"_L1) + u')';

    headerStr += "</div>\n"_L1;

    // ### iterate over the rest of strategy->headerToDisplay() (or
    // ### all headers if DefaultPolicy == Display) (elsewhere, too)
    return headerStr;
}
