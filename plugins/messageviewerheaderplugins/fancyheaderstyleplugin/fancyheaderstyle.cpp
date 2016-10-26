/*
   Copyright (C) 2013-2016 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "fancyheaderstyle.h"
#include "messageviewer_debug.h"
#include "messageviewer/headerstyle.h"
#include "messageviewer/headerstyle_util.h"

#include "messageviewer/headerstrategy.h"
#include <KTextToHTML>
#include "messageviewer/messageviewersettings.h"
#include <MimeTreeParser/NodeHelper>

#include <MessageCore/StringUtil>

#include <KLocalizedString>

#include <kcodecs.h>
#include <KColorScheme>

#include <QApplication>

#include <kmime/kmime_message.h>
#include <kmime/kmime_dateformatter.h>

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

FancyHeaderStyle::~FancyHeaderStyle()
{

}

const char *FancyHeaderStyle::name() const
{
    return "fancy";
}

QString FancyHeaderStyle::format(KMime::Message *message) const
{
    if (!message) {
        return QString();
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

    const QString spamHTML =  mHeaderStyleUtil.spamStatus(message);

    QString userHTML;
    MessageViewer::HeaderStyleUtil::xfaceSettings xface = mHeaderStyleUtil.xface(this, message);
    if (!xface.photoURL.isEmpty()) {
        //qCDebug(MESSAGEVIEWER_LOG) << "Got a photo:" << xface.photoURL;
        userHTML = QStringLiteral("<img src=\"%1\" width=\"%2\" height=\"%3\">")
                   .arg(xface.photoURL).arg(xface.photoWidth).arg(xface.photoHeight);
        userHTML = QLatin1String("<div class=\"senderpic\">") + userHTML + QLatin1String("</div>");
    }

    // the subject line and box below for details
    if (strategy->showHeader(QStringLiteral("subject"))) {
        const KTextToHTML::Options flags = KTextToHTML::PreserveSpaces | KTextToHTML::ReplaceSmileys;

        headerStr += QStringLiteral("<div dir=\"%1\">%2</div>\n")
                     .arg(subjectDir)
                     .arg(mHeaderStyleUtil.subjectString(message, flags));
    }
    headerStr += QLatin1String("<table class=\"outer\"><tr><td width=\"100%\"><table>\n");
    //headerStr += "<table>\n";
    // from line
    // the mailto: URLs can contain %3 etc., therefore usage of multiple
    // QString::arg is not possible
    if (strategy->showHeader(QStringLiteral("from"))) {

        const QVector<KMime::Types::Mailbox> resentFrom = mHeaderStyleUtil.resentFromList(message);
        headerStr += QStringLiteral("<tr><th>%1</th>\n"
                                    "<td>")
                     .arg(i18n("From: "))
                     + StringUtil::emailAddrAsAnchor(message->from(), StringUtil::DisplayFullAddress)
                     + (message->headerByType("Resent-From") ? QLatin1String("&nbsp;")
                        + i18n("(resent from %1)",
                               StringUtil::emailAddrAsAnchor(
                                   resentFrom, StringUtil::DisplayFullAddress))
                        : QString())
                     + (!vCardName().isEmpty() ? QLatin1String("&nbsp;&nbsp;<a href=\"") + vCardName() + QLatin1String("\">")
                        + i18n("[vCard]") + QLatin1String("</a>")
                        : QString())
                     + (!message->organization(false)
                        ? QString()
                        : QLatin1String("&nbsp;&nbsp;(")
                        + mHeaderStyleUtil.strToHtml(message->organization()->asUnicodeString())
                        + QLatin1Char(')'))
                     + QLatin1String("</td></tr>\n");
    }
    // to line
    if (strategy->showHeader(QStringLiteral("to"))) {
        const QVector<KMime::Types::Mailbox> resentTo = mHeaderStyleUtil.resentToList(message);

        QString to;
        if (message->headerByType("Resent-To")) {
            to = StringUtil::emailAddrAsAnchor(resentTo, StringUtil::DisplayFullAddress) + QLatin1Char(' ') + i18n("(receiver was %1)", StringUtil::emailAddrAsAnchor(message->to(), StringUtil::DisplayFullAddress,
                    QString(), StringUtil::ShowLink, StringUtil::ExpandableAddresses,
                    QStringLiteral("FullToAddressList")));
        } else {
            to = StringUtil::emailAddrAsAnchor(message->to(), StringUtil::DisplayFullAddress,
                                               QString(), StringUtil::ShowLink, StringUtil::ExpandableAddresses,
                                               QStringLiteral("FullToAddressList"));
        }

        headerStr.append(QStringLiteral("<tr><th>%1</th>\n"
                                        "<td>%2</td></tr>\n")
                         .arg(i18nc("To-field of the mail header.", "To: "))
                         .arg(to));
    }

    // cc line, if an
    if (strategy->showHeader(QStringLiteral("cc")) && message->cc(false)) {
        const QString str = StringUtil::emailAddrAsAnchor(message->cc(), StringUtil::DisplayFullAddress,
                            QString(), StringUtil::ShowLink, StringUtil::ExpandableAddresses,
                            QStringLiteral("FullCcAddressList"));
        if (!str.isEmpty()) {
            headerStr.append(QStringLiteral("<tr><th>%1</th>\n"
                                            "<td>%2</td></tr>\n")
                             .arg(i18n("CC: "))
                             .arg(str));
        }
    }

    // Bcc line, if any
    if (strategy->showHeader(QStringLiteral("bcc")) && message->bcc(false)) {
        const QString str = StringUtil::emailAddrAsAnchor(message->bcc(), StringUtil::DisplayFullAddress);
        if (!str.isEmpty()) {
            headerStr.append(QStringLiteral("<tr><th>%1</th>\n"
                                            "<td>%2</td></tr>\n")
                             .arg(i18n("BCC: "))
                             .arg(str));
        }
    }

    if (strategy->showHeader(QStringLiteral("date")))
        headerStr.append(QStringLiteral("<tr><th>%1</th>\n"
                                        "<td dir=\"%2\">%3</td></tr>\n")
                         .arg(i18n("Date: "))
                         .arg(mHeaderStyleUtil.directionOf(mHeaderStyleUtil.dateStr(message->date()->dateTime())))
                         .arg(mHeaderStyleUtil.strToHtml(mHeaderStyleUtil.dateString(message, isPrinting(), /* short = */ MessageViewer::HeaderStyleUtil::CustomDate))));
    if (MessageViewer::MessageViewerSettings::self()->showUserAgent()) {
        if (strategy->showHeader(QStringLiteral("user-agent"))) {
            if (auto hdr = message->userAgent(false)) {
                headerStr.append(QStringLiteral("<tr><th>%1</th>\n"
                                                "<td>%2</td></tr>\n")
                                 .arg(i18n("User-Agent: "))
                                 .arg(mHeaderStyleUtil.strToHtml(hdr->asUnicodeString())));
            }
        }

        if (strategy->showHeader(QStringLiteral("x-mailer"))) {
            if (auto hrd = message->headerByType("X-Mailer")) {
                headerStr.append(QStringLiteral("<tr><th>%1</th>\n"
                                                "<td>%2</td></tr>\n")
                                 .arg(i18n("X-Mailer: "))
                                 .arg(mHeaderStyleUtil.strToHtml(hrd->asUnicodeString())));
            }
        }
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
            headerStr.append(QStringLiteral("<tr><th>%1</th>\n"
                                            "<td>%2/%3, <strong>%4</strong></td></tr>\n")
                             .arg(i18n("Bugzilla: "))
                             .arg(mHeaderStyleUtil.strToHtml(product))
                             .arg(mHeaderStyleUtil.strToHtml(component))
                             .arg(mHeaderStyleUtil.strToHtml(status)));
        }
    }

    if (strategy->showHeader(QStringLiteral("disposition-notification-to"))){
        if (auto hrd = message->headerByType("Disposition-Notification-To")) {
            const QString to = hrd->asUnicodeString();
            headerStr.append(QStringLiteral("<tr><th>%1</th>\n"
                                            "<td>%2</tr>\n")
                             .arg(i18n("MDN To: "))
                             .arg(mHeaderStyleUtil.strToHtml(to)));
        }
    }

    if (!spamHTML.isEmpty())
        headerStr.append(QStringLiteral("<tr><td colspan=\"2\"><div class=\"spamheader\" dir=\"%1\"><b>%2</b>&nbsp;<span style=\"padding-left: 20px;\">%3</span></div></td></tr>\n")
                         .arg(subjectDir, i18n("Spam Status:"), spamHTML));

    headerStr.append(QLatin1String("<tr><td colspan=\"2\"><div id=\"attachmentInjectionPoint\"></div></td></tr>"));

    headerStr.append(
        QStringLiteral("</table></td><td align=\"center\">%1</td></tr></table>\n").arg(userHTML));

    headerStr += QLatin1String("</div>\n\n");
    return headerStr;
}

bool FancyHeaderStyle::hasAttachmentQuickList() const
{
    return true;
}
