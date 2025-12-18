/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

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

    const QString dir = QApplication::isRightToLeft() ? QStringLiteral("rtl") : QStringLiteral("ltr");
    QString headerStr = QStringLiteral("<div class=\"fancy header\" dir=\"%1\">\n").arg(dir);

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
        userHTML = QStringLiteral("<img src=\"%1\" width=\"%2\" height=\"%3\"/>").arg(xface.photoURL).arg(xface.photoWidth).arg(xface.photoHeight);
        userHTML = QLatin1StringView("<div class=\"senderpic\">") + userHTML + QLatin1StringView("</div>");
    }

    // the subject line and box below for details
    if (strategy->showHeader(QStringLiteral("subject"))) {
        const KTextToHTML::Options flags = KTextToHTML::PreserveSpaces | KTextToHTML::ReplaceSmileys;

        headerStr += QStringLiteral("<div dir=\"%1\">%2</div>\n").arg(subjectDir, mHeaderStyleUtil.subjectString(message, flags));
    }
    headerStr += QLatin1StringView("<table class=\"outer\"><tr><td width=\"100%\"><table>\n");
    // headerStr += "<table>\n";
    // from line
    // the mailto: URLs can contain %3 etc., therefore usage of multiple
    // QString::arg is not possible
    if (strategy->showHeader(QStringLiteral("from"))) {
        const auto resentFrom = mHeaderStyleUtil.resentFromList(message);
        headerStr += QStringLiteral(
                         "<tr><th>%1</th>\n"
                         "<td>")
                         .arg(i18n("From: "))
            + StringUtil::emailAddrAsAnchor(message->from(), StringUtil::DisplayFullAddress)
            + (message->headerByType("Resent-From")
                   ? QStringLiteral("&nbsp;") + i18n("(resent from %1)", StringUtil::emailAddrAsAnchor(resentFrom.data(), StringUtil::DisplayFullAddress))
                   : QString())
            + (!vCardName().isEmpty()
                   ? QStringLiteral("&nbsp;&nbsp;<a href=\"") + vCardName() + QStringLiteral("\">") + i18n("[vCard]") + QStringLiteral("</a>")
                   : QString())
            + (!message->organization(KMime::CreatePolicy::DontCreate)
                   ? QString()
                   : QStringLiteral("&nbsp;&nbsp;(") + mHeaderStyleUtil.strToHtml(message->organization()->asUnicodeString()) + QLatin1Char(')'))
            + QStringLiteral("</td></tr>\n");
    }
    // to line
    if (strategy->showHeader(QStringLiteral("to"))) {
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
                                                     QStringLiteral("FullToAddressList")));
        } else {
            to = StringUtil::emailAddrAsAnchor(message->to(),
                                               StringUtil::DisplayFullAddress,
                                               QString(),
                                               StringUtil::ShowLink,
                                               StringUtil::ExpandableAddresses,
                                               QStringLiteral("FullToAddressList"));
        }

        headerStr.append(QStringLiteral("<tr><th>%1</th>\n"
                                        "<td>%2</td></tr>\n")
                             .arg(i18nc("To-field of the mail header.", "To: "), to));
    }

    // cc line, if an
    if (strategy->showHeader(QStringLiteral("cc")) && message->cc(KMime::CreatePolicy::DontCreate)) {
        const QString str = StringUtil::emailAddrAsAnchor(message->cc(),
                                                          StringUtil::DisplayFullAddress,
                                                          QString(),
                                                          StringUtil::ShowLink,
                                                          StringUtil::ExpandableAddresses,
                                                          QStringLiteral("FullCcAddressList"));
        if (!str.isEmpty()) {
            headerStr.append(QStringLiteral("<tr><th>%1</th>\n"
                                            "<td>%2</td></tr>\n")
                                 .arg(i18n("CC: "), str));
        }
    }

    // Bcc line, if any
    if (strategy->showHeader(QStringLiteral("bcc")) && message->bcc(KMime::CreatePolicy::DontCreate)) {
        const QString str = StringUtil::emailAddrAsAnchor(message->bcc(), StringUtil::DisplayFullAddress);
        if (!str.isEmpty()) {
            headerStr.append(QStringLiteral("<tr><th>%1</th>\n"
                                            "<td>%2</td></tr>\n")
                                 .arg(i18n("BCC: "), str));
        }
    }

    if (strategy->showHeader(QStringLiteral("date"))) {
        headerStr.append(QStringLiteral("<tr><th>%1</th>\n"
                                        "<td dir=\"%2\">%3</td></tr>\n")
                             .arg(i18n("Date: "),
                                  mHeaderStyleUtil.directionOf(HeaderStyleUtil::dateStr(message->date()->dateTime())),
                                  mHeaderStyleUtil.strToHtml(HeaderStyleUtil::dateString(message, /* short = */ MessageViewer::HeaderStyleUtil::CustomDate))));
    }

    if (strategy->showHeader(QStringLiteral("x-bugzilla-url"))) {
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
                QStringLiteral("<tr><th>%1</th>\n"
                               "<td>%2/%3, <strong>%4</strong></td></tr>\n")
                    .arg(i18n("Bugzilla: "), mHeaderStyleUtil.strToHtml(product), mHeaderStyleUtil.strToHtml(component), mHeaderStyleUtil.strToHtml(status)));
        }
    }

    if (strategy->showHeader(QStringLiteral("disposition-notification-to"))) {
        if (auto hrd = message->headerByType("Disposition-Notification-To")) {
            const QString to = hrd->asUnicodeString();
            headerStr.append(QStringLiteral("<tr><th>%1</th>\n"
                                            "<td>%2</tr>\n")
                                 .arg(i18n("MDN To: "), mHeaderStyleUtil.strToHtml(to)));
        }
    }

    if (!spamHTML.isEmpty()) {
        headerStr.append(
            QStringLiteral(
                "<tr><td colspan=\"2\"><div class=\"spamheader\" dir=\"%1\"><b>%2</b>&nbsp;<span style=\"padding-left: 20px;\">%3</span></div></td></tr>\n")
                .arg(subjectDir, i18n("Spam Status:"), spamHTML));
    }

    headerStr.append(QStringLiteral("<tr><td colspan=\"2\"><div>%1</div></td></tr>").arg(attachmentHtml()));

    headerStr.append(QStringLiteral("</table></td><td align=\"center\">%1</td></tr></table>\n").arg(userHTML));

    headerStr += QLatin1StringView("</div>\n\n");
    return headerStr;
}
