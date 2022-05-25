/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "pgpkeyformatter.h"
#include "pgpkeymemento.h"
#include "pgpkeymessagepart.h"

#include <QApplication>
#include <QDebug>
#include <QPalette>

#include <MessageViewer/HtmlWriter>
#include <MimeTreeParser/MessagePart>

#include <GrantleeTheme/GrantleeKi18nLocalizer>
#include <GrantleeTheme/GrantleeThemeEngine>

#include <KLocalizedString>

using namespace MimeTreeParser::Interface;

MimeTreeParser::MessagePartPtr ApplicationPGPKeyFormatter::process(MimeTreeParser::Interface::BodyPart &part) const
{
    auto mp = new PgpKeyMessagePart(&part);
    auto m = dynamic_cast<PgpKeyMemento *>(mp->memento());

    if (!m && !mp->fingerprint().isEmpty()) {
        auto memento = new PgpKeyMemento();
        auto nodeHelper = part.nodeHelper();
        if (nodeHelper) {
            QObject::connect(memento, &PgpKeyMemento::update, nodeHelper, &MimeTreeParser::NodeHelper::update);
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

bool ApplicationPGPKeyFormatter::render(const MimeTreeParser::MessagePartPtr &msgPart,
                                        MessageViewer::HtmlWriter *htmlWriter,
                                        MessageViewer::RenderContext *context) const
{
    Q_UNUSED(context)
    auto mp = msgPart.dynamicCast<PgpKeyMessagePart>();
    if (!mp) {
        return false;
    }

    GrantleeTheme::Engine engine;
    engine.localizer()->setApplicationDomain(QByteArrayLiteral("messageviewer_application_gnupgwks_plugin"));

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    auto loader = QSharedPointer<Grantlee::FileSystemTemplateLoader>::create();
#else
    auto loader = QSharedPointer<KTextTemplate::FileSystemTemplateLoader>::create();
#endif
    loader->setTemplateDirs({QStringLiteral(":/")});
    engine.addTemplateLoader(loader);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    Grantlee::Template tpl = engine.loadByName(QStringLiteral("pgpkeymessagepart.html"));
#else
    KTextTemplate::Template tpl = engine.loadByName(QStringLiteral("pgpkeymessagepart.html"));
#endif
    if (tpl->error()) {
        qWarning() << tpl->errorString();
    }
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    Grantlee::Context ctx;
#else
    KTextTemplate::Context ctx;
#endif
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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    Grantlee::OutputStream s(htmlWriter->stream());
#else
    KTextTemplate::OutputStream s(htmlWriter->stream());
#endif
    tpl->render(&s, &ctx);
    return true;
}
