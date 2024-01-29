/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "gnupgwksformatter.h"
#include "gnupgwks_debug.h"
#include "gnupgwksmessagepart.h"

#include <QObject>
#include <QPalette>
#include <QUrl>
#include <QUrlQuery>
#include <QVariant>

#include <MessageCore/ColorUtil>
#include <MessageViewer/HtmlWriter>
#include <MessageViewer/Viewer>
#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/MessagePart>
#include <MimeTreeParser/NodeHelper>

#include <GrantleeTheme/GrantleeKi18nLocalizer>
#include <GrantleeTheme/GrantleeThemeEngine>
#include <KTextTemplate/Context>
#include <KTextTemplate/Template>

#include <QGpgME/DecryptJob>
#include <QGpgME/Protocol>

using namespace MimeTreeParser;
using namespace MimeTreeParser::Interface;

namespace
{
bool partHasMimeType(KMime::Content *part, const char *mt)
{
    const auto ct = part->contentType(false);
    return ct && ct->isMimeType(mt);
}
}

MessagePart::Ptr ApplicationGnuPGWKSFormatter::process(BodyPart &part) const
{
    const auto ct = part.content()->contentType(false);
    if (ct) {
        if (ct->isMimeType("multipart/mixed")) {
            const auto subParts = part.content()->contents();
            if (subParts.size() == 2 && partHasMimeType(subParts[0], "text/plain") && partHasMimeType(subParts[1], "application/vnd.gnupg.wks")) {
                return MimeMessagePart::Ptr(new MimeMessagePart(part.objectTreeParser(), subParts.at(1), false));
            } else {
                return MimeMessagePart::Ptr(new MimeMessagePart(part.objectTreeParser(), subParts.at(0), false));
            }
        }

        if (ct->isMimeType("application/vnd.gnupg.wks")) {
            const auto content = part.content()->decodedContent();
            if (content.startsWith("-----BEGIN PGP MESSAGE")) {
                auto decrypt = QGpgME::openpgp()->decryptJob();
                QByteArray plainText;
                auto result = decrypt->exec(part.content()->decodedContent(), plainText);
                if (result.error()) {
                    qCWarning(GNUPGWKS_LOG) << "Decryption failed!" << result.error().asString();
                    return {};
                }
                part.content()->setBody(plainText);
            }
            return MessagePart::Ptr(new GnuPGWKSMessagePart(&part));
        }
    }

    return {};
}

bool ApplicationGnuPGWKSFormatter::render(const MimeTreeParser::MessagePartPtr &msgPart,
                                          MessageViewer::HtmlWriter *htmlWriter,
                                          MessageViewer::RenderContext *context) const
{
    Q_UNUSED(context)
    auto mp = msgPart.dynamicCast<GnuPGWKSMessagePart>();
    if (!mp) {
        return false;
    }

    const QByteArray propertyName = "_GnuPGWKS" + mp->fingerprint().toLatin1();
    const bool hasError = (mp->nodeHelper()->property(propertyName.constData()).toString() == QLatin1StringView("error"));
    if (hasError) {
        mp->nodeHelper()->setProperty(propertyName.constData(), QVariant());
    }
    GrantleeTheme::Engine engine;
    engine.localizer()->setApplicationDomain(QByteArrayLiteral("messageviewer_application_gnupgwks_plugin"));
    auto loader = QSharedPointer<KTextTemplate::FileSystemTemplateLoader>::create();
    loader->setTemplateDirs({QStringLiteral(":/")});
    engine.addTemplateLoader(loader);
    KTextTemplate::Template tpl = engine.loadByName(QStringLiteral("gnupgwksmessagepart.html"));
    if (tpl->error()) {
        qCWarning(GNUPGWKS_LOG) << tpl->errorString();
    }
    KTextTemplate::Context ctx;
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
    KTextTemplate::OutputStream s(htmlWriter->stream());
    tpl->render(&s, &ctx);
    return true;
}
