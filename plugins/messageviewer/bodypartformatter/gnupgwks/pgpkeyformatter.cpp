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
#include <QDebug>

#include <MessageViewer/HtmlWriter>
#include <MimeTreeParser/MessagePart>

#include <GrantleeTheme/GrantleeThemeEngine>
#include <GrantleeTheme/GrantleeKi18nLocalizer>

#include <KLocalizedString>

using namespace MimeTreeParser::Interface;

MimeTreeParser::MessagePartPtr ApplicationPGPKeyFormatter::process(MimeTreeParser::Interface::BodyPart &part) const
{
    auto mp = new PgpKeyMessagePart(&part);
    PgpKeyMemento *m = dynamic_cast<PgpKeyMemento *>(mp->memento());

    if (!m && !mp->fingerprint().isEmpty()) {
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
        mp->setSearchRunning(memento->isRunning());
    } else if (mp->fingerprint().isEmpty()) {
        mp->setError(i18n("No valid key data in file."));
    } else if (m && m->isRunning()) {
        mp->setSearchRunning(m->isRunning());
        m = nullptr;
    }

    if (m) {
        mp->setSearchRunning(m->isRunning());
        Q_ASSERT(!m->isRunning());

        mp->setError(m->error());
        mp->setKey(m->key());
    }
    return MimeTreeParser::MessagePartPtr(mp);
}

bool ApplicationPGPKeyFormatter::render(const MimeTreeParser::MessagePartPtr &msgPart, MessageViewer::HtmlWriter *htmlWriter, MessageViewer::RenderContext *context) const
{
    Q_UNUSED(context);
    auto mp = msgPart.dynamicCast<PgpKeyMessagePart>();
    if (!mp) {
        return false;
    }

    GrantleeTheme::Engine engine;
    engine.localizer()->setApplicationDomain(QByteArrayLiteral("messageviewer_application_gnupgwks_plugin"));

    auto loader = QSharedPointer<Grantlee::FileSystemTemplateLoader>::create();
    loader->setTemplateDirs({QStringLiteral(":/")});
    engine.addTemplateLoader(loader);
    Grantlee::Template tpl = engine.loadByName(QStringLiteral("pgpkeymessagepart.html"));
    if (tpl->error()) {
        qWarning() << tpl->errorString();
    }
    Grantlee::Context ctx;
    ctx.setLocalizer(engine.localizer());

    QObject block;

    block.setProperty("showKeyDetails", context->showSignatureDetails());
    block.setProperty("error", mp->error());
    block.setProperty("importUrl", QString(mp->makeLink(QStringLiteral("pgpkey")) + QStringLiteral("?action=import")));
    block.setProperty("searchRunning", mp->searchRunning());
    const auto key = mp->key();
    block.setProperty("uid", mp->userID());
    block.setProperty("fingerprint", mp->fingerprint());
    QLocale l;
    block.setProperty("created", l.toString(mp->keyDate(), QLocale::ShortFormat));
    if (!key.isNull()) {
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
