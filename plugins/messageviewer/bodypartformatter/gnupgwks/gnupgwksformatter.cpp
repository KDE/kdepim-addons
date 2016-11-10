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

#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/HtmlWriter>
#include <MimeTreeParser/NodeHelper>
#include <MessageCore/MessageCoreUtil>
#include <MessageViewer/Viewer>

#include <GrantleeTheme/GrantleeThemeEngine>
#include <GrantleeTheme/GrantleeKi18nLocalizer>
#include <GrantleeTheme/QtResourceTemplateLoader>
#include <grantlee/context.h>
#include <grantlee/template.h>

using namespace MimeTreeParser::Interface;

BodyPartFormatter::Result ApplicationGnuPGWKSFormatter::format(BodyPart *part, MimeTreeParser::HtmlWriter *writer) const
{
    return format(part, writer, Q_NULLPTR);
}

BodyPartFormatter::Result ApplicationGnuPGWKSFormatter::format(BodyPart *part, MimeTreeParser::HtmlWriter *writer,
        QObject *) const
{
    if (!writer) {
        return Ok;
    }

    GnuPGWKSMessagePart mp(part);

    const QByteArray propertyName = "_GnuPGWKS" + mp.fingerprint().toLatin1();
    const bool hasError = (part->nodeHelper()->property(propertyName).toString() == QLatin1String("error"));
    if (hasError) {
        part->nodeHelper()->setProperty(propertyName, QVariant());
    }

    GrantleeTheme::Engine engine;
    engine.localizer()->setApplicationDomain(QByteArrayLiteral("messageviewer_application_gnupgwks_plugin"));
    engine.addTemplateLoader(QSharedPointer<GrantleeTheme::QtResourceTemplateLoader>::create());

    Grantlee::Template tpl = engine.loadByName(QStringLiteral(":/gnupgwksmessagepart.html"));
    Grantlee::Context ctx;
    ctx.setLocalizer(engine.localizer());

    QObject block;

    const auto baseUrl = QStringLiteral("gnupgwks?%1");
    block.setProperty("isRequest", mp.confirmationType() == GnuPGWKSMessagePart::ConfirmationRequest);
    block.setProperty("isResponse", mp.confirmationType() == GnuPGWKSMessagePart::ConfirmationResponse);
    QUrlQuery confirmQuery;
    confirmQuery.addQueryItem(QStringLiteral("action"), QStringLiteral("confirm"));
    confirmQuery.addQueryItem(QStringLiteral("fpr"), mp.fingerprint());
    block.setProperty("confirmUrl", mp.part()->makeLink(baseUrl.arg(confirmQuery.toString(QUrl::FullyDecoded))));
    QUrlQuery keyQuery;
    keyQuery.addQueryItem(QStringLiteral("action"), QStringLiteral("show"));
    keyQuery.addQueryItem(QStringLiteral("fpr"), mp.fingerprint());
    block.setProperty("keyUrl", mp.part()->makeLink(baseUrl.arg(keyQuery.toString(QUrl::FullyDecoded))));
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

    writer->queue(tpl->render(&ctx));
    return Ok;
}
