/*
  Copyright (c) 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   This library is free software; you can redistribute it and/or modify it
   under the terms of the GNU Library General Public License as published by
   the Free Software Foundation; either version 2 of the License, or (at your
   option) any later version.

   This library is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
   License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to the
   Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA.
*/

#include "gnupgwksformatter.h"
#include "gnupgwksmessagepart.h"

#include <QObject>
#include <QVariant>
#include <QPalette>
#include <QUrl>
#include <QUrlQuery>

#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/HtmlWriter>
#include <MimeTreeParser/NodeHelper>
#include <MimeTreeParser/MessagePart>
#include <MessageCore/MessageCoreUtil>
#include <MessageViewer/Viewer>

#include <GrantleeTheme/GrantleeThemeEngine>
#include <GrantleeTheme/GrantleeKi18nLocalizer>
#include <GrantleeTheme/QtResourceTemplateLoader>
#include <grantlee/context.h>
#include <grantlee/template.h>

#include <QGpgME/Protocol>
#include <QGpgME/DecryptJob>

using namespace MimeTreeParser;
using namespace MimeTreeParser::Interface;

namespace {
bool partHasMimeType(KMime::Content *part, const char *mt)
{
    const auto ct = part->contentType(false);
    return ct && ct->isMimeType(mt);
}
}

MessagePart::Ptr ApplicationGnuPGWKSFormatter::process(BodyPart &part) const
{
    const auto ct = part.content()->contentType(false);
    if (ct && ct->isMimeType("multipart/mixed")) {
        const auto subParts = part.content()->contents();
        if (subParts.size() == 2
            && partHasMimeType(subParts[0], "text/plain")
            && partHasMimeType(subParts[1], "application/vnd.gnupg.wks")) {
            return MimeMessagePart::Ptr(new MimeMessagePart(part.objectTreeParser(), subParts.at(1), false));
        } else {
            return MimeMessagePart::Ptr(new MimeMessagePart(part.objectTreeParser(), subParts.at(0), false));
        }
    }

    if (ct && ct->isMimeType("application/vnd.gnupg.wks")) {
        const auto content = part.content()->decodedContent();
        if (content.startsWith("-----BEGIN PGP MESSAGE")) {
            auto decrypt = QGpgME::openpgp()->decryptJob();
            QByteArray plainText;
            auto result = decrypt->exec(part.content()->decodedContent(), plainText);
            if (result.error()) {
                qWarning() << "Decryption failed!" << result.error().asString();
                return {};
            }
            part.content()->setBody(plainText);
        }
        return MessagePart::Ptr(new GnuPGWKSMessagePart(&part));
    }

    return {};
}

bool ApplicationGnuPGWKSFormatter::render(const MimeTreeParser::MessagePartPtr &msgPart, MimeTreeParser::HtmlWriter *htmlWriter, MessageViewer::RenderContext *context) const
{
    Q_UNUSED(context);
    auto mp = msgPart.dynamicCast<GnuPGWKSMessagePart>();
    if (!mp) {
        return false;
    }

    const QByteArray propertyName = "_GnuPGWKS" + mp->fingerprint().toLatin1();
    const bool hasError = (mp->nodeHelper()->property(propertyName).toString() == QLatin1String("error"));
    if (hasError) {
        mp->nodeHelper()->setProperty(propertyName, QVariant());
    }

    GrantleeTheme::Engine engine;
    engine.localizer()->setApplicationDomain(QByteArrayLiteral("messageviewer_application_gnupgwks_plugin"));
    engine.addTemplateLoader(QSharedPointer<GrantleeTheme::QtResourceTemplateLoader>::create());

    Grantlee::Template tpl = engine.loadByName(QStringLiteral(":/gnupgwksmessagepart.html"));
    Grantlee::Context ctx;
    ctx.setLocalizer(engine.localizer());

    QObject block;

    const auto baseUrl = QStringLiteral("gnupgwks?%1");
    block.setProperty("isRequest", mp->confirmationType() == GnuPGWKSMessagePart::ConfirmationRequest);
    block.setProperty("isResponse", mp->confirmationType() == GnuPGWKSMessagePart::ConfirmationResponse);
    QUrlQuery confirmQuery;
    confirmQuery.addQueryItem(QStringLiteral("action"), QStringLiteral("confirm"));
    confirmQuery.addQueryItem(QStringLiteral("fpr"), mp->fingerprint());
    block.setProperty("confirmUrl", mp->makeLink(baseUrl.arg(confirmQuery.toString(QUrl::FullyDecoded))));
    QUrlQuery keyQuery;
    keyQuery.addQueryItem(QStringLiteral("action"), QStringLiteral("show"));
    keyQuery.addQueryItem(QStringLiteral("fpr"), mp->fingerprint());
    block.setProperty("keyUrl", mp->makeLink(baseUrl.arg(keyQuery.toString(QUrl::FullyDecoded))));
    block.setProperty("hasError", hasError);
    ctx.insert(QStringLiteral("block"), &block);

    QObject style;
    QPalette p;
    p.setCurrentColorGroup(QPalette::Normal);
    style.setProperty("buttonBg", p.color(QPalette::Button).name());
    style.setProperty("buttonBorder", p.shadow().color().name());
    p.setCurrentColorGroup(QPalette::Active);
    style.setProperty("buttonBorderHl", p.shadow().color().name());
    p.setCurrentColorGroup(QPalette::Normal);
    style.setProperty("buttonFg", p.color(QPalette::ButtonText).name());
    style.setProperty("errorFg", MessageCore::ColorUtil::self()->pgpSignedBadTextColor().name());
    ctx.insert(QStringLiteral("style"), &style);

    Grantlee::OutputStream s(htmlWriter->stream());
    tpl->render(&s, &ctx);
    return true;
}
