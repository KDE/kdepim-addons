/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "enterpriseheaderstyle.h"
#include <MessageViewer/MessageViewerSettings>

#include <MessageViewer/HeaderStrategy>

#include <MessageCore/StringUtil>

#include <KColorScheme>
#include <KLocalizedString>

#include <QStandardPaths>

using namespace MessageCore;
using namespace MessageViewer;

QString EnterpriseHeaderStyle::format(KMime::Message *message) const
{
    if (!message) {
        return {};
    }
    const HeaderStrategy *strategy = headerStrategy();
    // The direction of the header is determined according to the direction
    // of the application layout.
    // However, the direction of the message subject within the header is
    // determined according to the contents of the subject itself. Since
    // the "Re:" and "Fwd:" prefixes would always cause the subject to be
    // considered left-to-right, they are ignored when determining its
    // direction.

    // colors depend on if it is encapsulated or not
    QColor fontColor(Qt::white);
    QString linkColor = QStringLiteral("class =\"white\"");
    if (!mActiveColor.isValid()) {
        mActiveColor = KColorScheme(QPalette::Active, KColorScheme::Selection).background().color();
    }
    QColor activeColorDark = mActiveColor.darker(130);
    // reverse colors for encapsulated
    if (!isTopLevel()) {
        activeColorDark = mActiveColor.darker(50);
        fontColor = QColor(Qt::black);
        linkColor = QStringLiteral("class =\"black\"");
    }

    QString imgpath(QStandardPaths::locate(QStandardPaths::GenericDataLocation, QStringLiteral("libmessageviewer/pics/"), QStandardPaths::LocateDirectory));
    imgpath.prepend(QLatin1StringView("file://"));
    imgpath.append(QLatin1StringView("enterprise_"));
    const QString borderSettings(QStringLiteral(" padding-top: 0px; padding-bottom: 0px; border-width: 0px "));
    QString headerStr;

    // 3D borders
    if (isTopLevel()) {
        headerStr += QLatin1StringView(
            "<div style=\"position: fixed; top: 0px; left: 0px; background-color: #606060; "
            "width: 10px; min-height: 100%;\">&nbsp;</div>"
            "<div style=\"position: fixed; top: 0px; right: 0px;  background-color: #606060; "
            "width: 10px; min-height: 100%;\">&nbsp;</div>");
    }

    headerStr += QStringLiteral("<div style=\"margin-left: 10px; top: 0px;\"><span style=\"font-size: 0.8em; font-weight: bold;\">")
        + HeaderStyleUtil::dateString(message, /* shortDate */ MessageViewer::HeaderStyleUtil::CustomDate)
        + QStringLiteral(
                     "</span></div>"
                     // #0057ae
                     "<table style=\"background: ")
        + activeColorDark.name()
        + QStringLiteral(
                     "; border-collapse:collapse; top: 14px; min-width: 200px; \" cellpadding='0'> \n"
                     "  <tr> \n"
                     "   <td style=\"min-width: 6px; background-image: url(")
        + imgpath
        + QStringLiteral(
                     "top_left.png); \"></td> \n"
                     "   <td style=\"height: 6px; width: 100%; background: url(")
        + imgpath
        + QStringLiteral(
                     "top.png); \"></td> \n"
                     "   <td style=\"min-width: 6px; background: url(")
        + imgpath
        + QStringLiteral(
                     "top_right.png); \"></td> </tr> \n"
                     "   <tr> \n"
                     "   <td style=\"min-width: 6px; max-width: 6px; background: url(")
        + imgpath
        + QStringLiteral(
                     "left.png); \"></td> \n"
                     "   <td style=\"\"> \n");
    headerStr += QStringLiteral(
                     "<div class=\"noprint\" style=\"z-index: 1; float:right; position: relative; top: -35px; right: 20px ; max-height: 65px\">\n"
                     "<img src=\"")
        + imgpath
        + QStringLiteral(
                     "icon.png\"/>\n"
                     "</div>\n");
    headerStr += QLatin1StringView("    <table style=\"color: ") + fontColor.name()
        + QLatin1StringView(" ! important; margin: 1px; border-spacing: 0px;\" cellpadding='0'> \n");

    // subject
    if (strategy->showHeader(QStringLiteral("subject"))) {
        const KTextToHTML::Options flags = KTextToHTML::PreserveSpaces | KTextToHTML::ReplaceSmileys;

        headerStr += QStringLiteral(
                         "     <tr> \n"
                         "      <td style=\"font-size: 0.5em; text-align: right; padding-left: 5px; padding-right: 24px; ")
            + borderSettings
            + QStringLiteral(
                         "\"></td> \n"
                         "      <td style=\"font-weight: bolder; font-size: 120%; padding-right: 91px; ")
            + borderSettings + QStringLiteral("\">");
        headerStr += mHeaderStyleUtil.subjectString(message, flags)
            + QStringLiteral(
                         "</td> \n"
                         "     </tr> \n");
    }

    // from
    if (strategy->showHeader(QStringLiteral("from"))) {
        // We by design use the stripped mail address here, it is more enterprise-like.
        QString fromPart = StringUtil::emailAddrAsAnchor(message->from(), StringUtil::DisplayFullAddress, linkColor);
        if (!vCardName().isEmpty()) {
            fromPart += QLatin1StringView("&nbsp;&nbsp;<a href=\"") + vCardName() + QLatin1StringView("\" ") + linkColor + QLatin1Char('>') + i18n("[vCard]")
                + QLatin1StringView("</a>");
        }
        // TDDO strategy date
        // if ( strategy->showHeader( "date" ) )
        headerStr += QStringLiteral(
                         "     <tr> \n"
                         "      <td style=\"font-size: 0.8em; padding-left: 5px; padding-right: 24px; text-align: right; vertical-align:top; ")
            + borderSettings + QLatin1StringView("\">") + i18n("From: ")
            + QStringLiteral(
                         "</td> \n"
                         "      <td style=\"")
            + borderSettings + QStringLiteral("\">") + fromPart
            + QStringLiteral(
                         "</td> "
                         "     </tr> ");
    }

    // to line
    if (strategy->showHeader(QStringLiteral("to"))) {
        headerStr += QStringLiteral(
                         "     <tr> "
                         "      <td style=\"font-size: 0.8em; text-align: right; vertical-align:top; padding-left: 5px; padding-right: 24px; ")
            + borderSettings + QLatin1StringView("\">") + i18n("To: ")
            + QStringLiteral(
                         "</td> "
                         "      <td style=\"")
            + borderSettings + QStringLiteral("\">") + StringUtil::emailAddrAsAnchor(message->to(), StringUtil::DisplayFullAddress, linkColor)
            + QStringLiteral(
                         "      </td> "
                         "     </tr>\n");
    }

    // cc line, if any
    if (strategy->showHeader(QStringLiteral("cc")) && message->cc(KMime::CreatePolicy::DontCreate)) {
        headerStr += QStringLiteral(
                         "     <tr> "
                         "      <td style=\"font-size: 0.8em; text-align: right; vertical-align:top; padding-left: 5px; padding-right: 24px; ")
            + borderSettings + QLatin1StringView("\">") + i18n("CC: ")
            + QStringLiteral(
                         "</td> "
                         "      <td style=\"")
            + borderSettings + QStringLiteral("\">") + StringUtil::emailAddrAsAnchor(message->cc(), StringUtil::DisplayFullAddress, linkColor)
            + QStringLiteral(
                         "      </td> "
                         "     </tr>\n");
    }

    // bcc line, if any
    if (strategy->showHeader(QStringLiteral("bcc")) && message->bcc(KMime::CreatePolicy::DontCreate)) {
        headerStr += QStringLiteral(
                         "     <tr> "
                         "      <td style=\"font-size: 0.8em; text-align: right; vertical-align:top; padding-left: 5px; padding-right: 24px; ")
            + borderSettings + QLatin1StringView("\">") + i18n("BCC: ")
            + QStringLiteral(
                         "</td> "
                         "      <td style=\"")
            + borderSettings + QStringLiteral("\">") + StringUtil::emailAddrAsAnchor(message->bcc(), StringUtil::DisplayFullAddress, linkColor)
            + QStringLiteral(
                         "      </td> "
                         "     </tr>\n");
    }

    // attachments
    QString attachment;
    if (isTopLevel()) {
        attachment = QStringLiteral(
                         "<tr>"
                         "<td style='min-width: 6px; max-width: 6px; background: url(")
            + imgpath
            + QStringLiteral(
                  "left.png);'></td>"
                  "<td style='padding-right:20px;'>"
                  "<div class=\"noprint\" >"
                  "<div>%1</div>"
                  "</div>"
                  "</td>"
                  "<td style='min-width: 6px; max-width: 6px; background: url(")
                  .arg(attachmentHtml())
            + imgpath
            + QStringLiteral(
                         "right.png);'></td>"
                         "</tr>");
    }

    // header-bottom
    headerStr += QStringLiteral(
                     "    </table> \n"
                     "   </td> \n"
                     "   <td style=\"min-width: 6px; max-height: 15px; background: url(")
        + imgpath
        + QStringLiteral(
                     "right.png); \"></td> \n"
                     "  </tr> \n")
        + attachment
        + QStringLiteral(
                     "  <tr> \n"
                     "   <td style=\"min-width: 6px; background: url(")
        + imgpath
        + QStringLiteral(
                     "s_left.png); \"></td> \n"
                     "   <td style=\"height: 35px; width: 80%; background: url(")
        + imgpath
        + QStringLiteral(
                     "sbar.png);\"> \n"
                     "    <img src=\"")
        + imgpath
        + QStringLiteral(
                     "sw.png\" style=\"margin: 0px; height: 30px; overflow:hidden; \"/> \n"
                     "    <img src=\"")
        + imgpath
        + QStringLiteral(
                     "sp_right.png\" style=\"float: right; \"/> </td> \n"
                     "   <td style=\"min-width: 6px; background: url(")
        + imgpath
        + QStringLiteral(
                     "s_right.png); \"></td> \n"
                     "  </tr> \n"
                     " </table> \n");

    if (isPrinting()) {
        // provide a bit more left padding when printing
        // kolab/issue3254 (printed mail cut at the left side)
        headerStr += QLatin1StringView("<div style=\"padding: 6px; padding-left: 10px;\">");
    } else {
        headerStr += QLatin1StringView("<div style=\"padding: 6px;\">");
    }

    // TODO
    // spam status
    // ### iterate over the rest of strategy->headerToDisplay() (or
    // ### all headers if DefaultPolicy == Display) (elsewhere, too)
    return headerStr;
}

const char *MessageViewer::EnterpriseHeaderStyle::name() const
{
    return "enterprise";
}
