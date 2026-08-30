/*
   SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "fancyheaderstyle.h"

#include <KTextToHTML>
#include <MessageViewer/HeaderStrategy>
#include <MessageViewer/MessageViewerSettings>
#include <MimeTreeParser/NodeHelper>

#include <MessageCore/StringUtil>

#include <KLocalizedString>

#include <QApplication>
using namespace Qt::Literals::StringLiterals;

using namespace MessageCore;

using namespace MessageViewer;
//
// FancyHeaderStyle:
//   Like PlainHeaderStyle, but with slick frames and background colours.
//

FancyHeaderStyle::FancyHeaderStyle()
    : HeaderStyle()
{
}

FancyHeaderStyle::~FancyHeaderStyle() = default;

const char *FancyHeaderStyle::name() const
{
    return "fancy";
}

QString FancyHeaderStyle::format(KMime::Message *message) const
{
    if (!message) {
        return {};
    }
    const HeaderStrategy *strategy = headerStrategy();
    // ### from kmreaderwin begin
    // The direction of the header is determined according to the direction
    // of the application layout.

    const QString dir = QApplication::isRightToLeft() ? u"rtl"_s : u"ltr"_s;
    QString headerStr = u"<div class=\"fancy header\" dir=\"%1\">\n"_s.arg(dir);

    // However, the direction of the message subject within the header is
    // determined according to the contents of the subject itself. Since
    // the "Re:" and "Fwd:" prefixes would always cause the subject to be
    // considered left-to-right, they are ignored when determining its
    // direction.

    const QString subjectDir = mHeaderStyleUtil.subjectDirectionString(message);

    // Spam header display.
    // If the spamSpamStatus config value is true then we look for headers
    // from a few spam filters and try to create visually meaningful graphics
    // out of the spam scores.

    const QString spamHTML = mHeaderStyleUtil.spamStatus(message);

    QString userHTML;
    MessageViewer::HeaderStyleUtil::xfaceSettings xface = mHeaderStyleUtil.xface(this, message);
    if (!xface.photoURL.isEmpty()) {
        // qCDebug(MESSAGEVIEWER_LOG) << "Got a photo:" << xface.photoURL;
        userHTML = u"<img src=\"%1\" width=\"%2\" height=\"%3\"/>"_s.arg(xface.photoURL).arg(xface.photoWidth).arg(xface.photoHeight);
        userHTML = QLatin1StringView("<div class=\"senderpic\">") + userHTML + QLatin1StringView("</div>");
    }

    // the subject line and box below for details
    if (strategy->showHeader(u"subject"_s)) {
        const KTextToHTML::Options flags = KTextToHTML::PreserveSpaces | KTextToHTML::ReplaceSmileys;

        headerStr += u"<div dir=\"%1\">%2</div>\n"_s.arg(subjectDir, mHeaderStyleUtil.subjectString(message, flags));
    }
    headerStr += QLatin1StringView("<table class=\"outer\"><tr><td width=\"100%\"><table>\n");
    // headerStr += "<table>\n";
    // from line
    // the mailto: URLs can contain %3 etc., therefore usage of multiple
    // QString::arg is not possible
    if (strategy->showHeader(u"from"_s)) {
        const auto resentFrom = mHeaderStyleUtil.resentFromList(message);
        headerStr +=
            u"<tr><th>%1</th>\n"
            "<td>"_s.arg(i18n("From: "))
            + StringUtil::emailAddrAsAnchor(message->from(), StringUtil::DisplayFullAddress)
            + (message->headerByType("Resent-From")
                   ? u"&nbsp;"_s + i18n("(resent from %1)", StringUtil::emailAddrAsAnchor(resentFrom.data(), StringUtil::DisplayFullAddress))
                   : QString())
            + (!vCardName().isEmpty() ? u"&nbsp;&nbsp;<a href=\""_s + vCardName() + u"\">"_s + i18n("[vCard]") + u"</a>"_s : QString())
            + (!message->organization(KMime::CreatePolicy::DontCreate)
                   ? QString()
                   : u"&nbsp;&nbsp;("_s + mHeaderStyleUtil.strToHtml(message->organization()->asUnicodeString()) + QLatin1Char(')'))
            + u"</td></tr>\n"_s;
    }
    // to line
    if (strategy->showHeader(u"to"_s)) {
        const auto resentTo = mHeaderStyleUtil.resentToList(message);

        QString to;
        if (resentTo.data()) {
            to = StringUtil::emailAddrAsAnchor(resentTo.data(), StringUtil::DisplayFullAddress) + QLatin1Char(' ')
                + i18n("(receiver was %1)",
                       StringUtil::emailAddrAsAnchor(message->to(),
                                                     StringUtil::DisplayFullAddress,
                                                     QString(),
                                                     StringUtil::ShowLink,
                                                     StringUtil::ExpandableAddresses,
                                                     u"FullToAddressList"_s));
        } else {
            to = StringUtil::emailAddrAsAnchor(message->to(),
                                               StringUtil::DisplayFullAddress,
                                               QString(),
                                               StringUtil::ShowLink,
                                               StringUtil::ExpandableAddresses,
                                               u"FullToAddressList"_s);
        }

        headerStr.append(
            u"<tr><th>%1</th>\n"
            "<td>%2</td></tr>\n"_s.arg(i18nc("To-field of the mail header.", "To: "), to));
    }

    // cc line, if an
    if (strategy->showHeader(u"cc"_s) && message->cc(KMime::CreatePolicy::DontCreate)) {
        const QString str = StringUtil::emailAddrAsAnchor(message->cc(),
                                                          StringUtil::DisplayFullAddress,
                                                          QString(),
                                                          StringUtil::ShowLink,
                                                          StringUtil::ExpandableAddresses,
                                                          u"FullCcAddressList"_s);
        if (!str.isEmpty()) {
            headerStr.append(
                u"<tr><th>%1</th>\n"
                "<td>%2</td></tr>\n"_s.arg(i18n("CC: "), str));
        }
    }

    // Bcc line, if any
    if (strategy->showHeader(u"bcc"_s) && message->bcc(KMime::CreatePolicy::DontCreate)) {
        const QString str = StringUtil::emailAddrAsAnchor(message->bcc(), StringUtil::DisplayFullAddress);
        if (!str.isEmpty()) {
            headerStr.append(
                u"<tr><th>%1</th>\n"
                "<td>%2</td></tr>\n"_s.arg(i18n("BCC: "), str));
        }
    }

    if (strategy->showHeader(u"date"_s)) {
        headerStr.append(
            u"<tr><th>%1</th>\n"
            "<td dir=\"%2\">%3</td></tr>\n"_s.arg(
                i18n("Date: "),
                mHeaderStyleUtil.directionOf(HeaderStyleUtil::dateStr(message->date()->dateTime())),
                mHeaderStyleUtil.strToHtml(HeaderStyleUtil::dateString(message, /* short = */ MessageViewer::HeaderStyleUtil::CustomDate))));
    }

    if (strategy->showHeader(u"x-bugzilla-url"_s)) {
        if (message->hasHeader("X-Bugzilla-URL")) {
            QString product;
            if (auto hrd = message->headerByType("X-Bugzilla-Product")) {
                product = hrd->asUnicodeString();
            }
            QString component;
            if (auto hrd = message->headerByType("X-Bugzilla-Component")) {
                component = hrd->asUnicodeString();
            }
            QString status;
            if (auto hrd = message->headerByType("X-Bugzilla-Status")) {
                status = hrd->asUnicodeString();
            }
            headerStr.append(
                u"<tr><th>%1</th>\n"
                "<td>%2/%3, <strong>%4</strong></td></tr>\n"_s
                    .arg(i18n("Bugzilla: "), mHeaderStyleUtil.strToHtml(product), mHeaderStyleUtil.strToHtml(component), mHeaderStyleUtil.strToHtml(status)));
        }
    }

    if (strategy->showHeader(u"disposition-notification-to"_s)) {
        if (auto hrd = message->headerByType("Disposition-Notification-To")) {
            const QString to = hrd->asUnicodeString();
            headerStr.append(
                u"<tr><th>%1</th>\n"
                "<td>%2</tr>\n"_s.arg(i18n("MDN To: "), mHeaderStyleUtil.strToHtml(to)));
        }
    }

    if (!spamHTML.isEmpty()) {
        headerStr.append(
            u"<tr><td colspan=\"2\"><div class=\"spamheader\" dir=\"%1\"><b>%2</b>&nbsp;<span style=\"padding-left: 20px;\">%3</span></div></td></tr>\n"_s
                .arg(subjectDir, i18n("Spam Status:"), spamHTML));
    }

    headerStr.append(u"<tr><td colspan=\"2\"><div>%1</div></td></tr>"_s.arg(attachmentHtml()));

    headerStr.append(u"</table></td><td align=\"center\">%1</td></tr></table>\n"_s.arg(userHTML));

    headerStr += QLatin1StringView("</div>\n\n");
    return headerStr;
}
