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

#include "pgpkeyformatter.h"
#include "pgpkeymessagepart.h"
#include "pgpkeymemento.h"

#include <QApplication>
#include <QPalette>

#include <MimeTreeParser/HtmlWriter>
#include <MimeTreeParser/MessagePart>

#include <GrantleeTheme/GrantleeThemeEngine>
#include <GrantleeTheme/QtResourceTemplateLoader>
#include <GrantleeTheme/GrantleeKi18nLocalizer>

#include <KLocalizedString>

using namespace MimeTreeParser::Interface;

MimeTreeParser::MessagePartPtr ApplicationPGPKeyFormatter::process(MimeTreeParser::Interface::BodyPart& part) const
{
    auto mp = new PgpKeyMessagePart(&part);
    PgpKeyMemento *m = dynamic_cast<PgpKeyMemento *>(mp->memento());

    if (!m) {
        auto memento = new PgpKeyMemento();
        auto nodeHelper = part.nodeHelper();
        if (nodeHelper) {
            QObject::connect(memento, &PgpKeyMemento::update,
                             nodeHelper, &MimeTreeParser::NodeHelper::update);
            memento->start(mp->fingerprint());
        } else {
            memento->exec(mp->fingerprint());
            m = memento;
        }
        mp->setMemento(memento);
    } else if (m->isRunning()) {
        m = nullptr;
    }

    if (m) {
        Q_ASSERT(!m->isRunning());

        mp->setError(m->error());
        mp->setKey(m->key());
    }
    return MimeTreeParser::MessagePartPtr(mp);
}

bool ApplicationPGPKeyFormatter::render(const MimeTreeParser::MessagePartPtr &msgPart, MimeTreeParser::HtmlWriter *htmlWriter, MessageViewer::RenderContext *context) const
{
    Q_UNUSED(context);
    auto mp = msgPart.dynamicCast<PgpKeyMessagePart>();
    if (!mp)
        return false;

    GrantleeTheme::Engine engine;
    engine.localizer()->setApplicationDomain(QByteArrayLiteral("messageviewer_application_gnupgwks_plugin"));
    engine.addTemplateLoader(QSharedPointer<GrantleeTheme::QtResourceTemplateLoader>::create());

    Grantlee::Template tpl = engine.loadByName(QStringLiteral(":/pgpkeymessagepart.html"));
    Grantlee::Context ctx;
    ctx.setLocalizer(engine.localizer());

    QObject block;

    block.setProperty("showKeyDetails", mp->source()->showSignatureDetails());
    block.setProperty("error", mp->error());
    block.setProperty("importUrl", mp->makeLink(QStringLiteral("pgpkey")) + QStringLiteral("?action=import"));
    const auto key = mp->key();
    if (key.isNull()) {
        block.setProperty("uid", mp->userID());
        block.setProperty("fingerprint", mp->fingerprint());
        block.setProperty("created", mp->keyDate().toString(Qt::SystemLocaleDate));
    } else {
        const auto uid = key.userID(0);
        block.setProperty("hasKey", true);
        if (uid.email() && *uid.email() && uid.name() && *uid.name()) {
            block.setProperty("uid", QStringLiteral("%1 <%2>").arg(QString::fromUtf8(uid.name()),
                                                                   QString::fromUtf8(uid.email())));
        } else if (uid.name() && *uid.name()) {
            block.setProperty("uid", QString::fromUtf8(uid.name()));
        } else if (uid.email() && *uid.email()) {
            block.setProperty("uid", QString::fromUtf8(uid.email()));
        } else {
            block.setProperty("uid", i18n("Unknown identity"));
        }
        block.setProperty("created", QDateTime::fromTime_t(key.subkey(0).creationTime()).toString(Qt::SystemLocaleDate));
        block.setProperty("fingerprint", QString::fromLatin1(key.primaryFingerprint()));
        block.setProperty("keyUrl", QStringLiteral("kmail:showCertificate#GpgME ### gpgme ### %1").arg(QString::fromLatin1(key.keyID())));
    }

    QObject style;
    const auto bgColor = QApplication::palette().color(QPalette::Base);
    if (bgColor.value() < 128) { // HSV value (brightness): 0 = darkest, 255 = brightest
        style.setProperty("borderColor", QColor(Qt::white).name());
        style.setProperty("frameTextColor", QColor(Qt::black).name());
    } else {
        style.setProperty("borderColor", QColor(Qt::black).name());
        style.setProperty("frameTextColor", QColor(Qt::white).name());
    }

    ctx.insert(QStringLiteral("block"), &block);
    ctx.insert(QStringLiteral("style"), &style);
    Grantlee::OutputStream s(htmlWriter->stream());
    tpl->render(&s, &ctx);
    return true;
}
