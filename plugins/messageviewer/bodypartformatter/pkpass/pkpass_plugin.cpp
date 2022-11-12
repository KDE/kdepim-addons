/*
   SPDX-FileCopyrightText: 2017 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include <MessageViewer/MessagePartRenderPlugin>
#include <MessageViewer/MessagePartRendererBase>
#include <MessageViewer/MessagePartRendererManager>

#include <MessageViewer/HtmlWriter>
#include <MimeTreeParser/MessagePart>

#include <KPkPass/Barcode>
#include <KPkPass/BoardingPass>

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <grantlee/metatype.h>
#include <grantlee/template.h>
#else
#include <KTextTemplate/MetaType>
#include <KTextTemplate/Template>
#endif

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <prison/Prison>
#else
#include <Prison/Prison>
#endif

#include <QGuiApplication>
#include <QUrl>

static bool isPkPassContent(KMime::Content *content)
{
    const auto ct = content->contentType(false);
    const QByteArray mimetype = ct ? ct->mimeType() : QByteArray();
    if (mimetype == "application/vnd.apple.pkpass") {
        return true;
    }
    if (mimetype != "application/octet-stream" && mimetype != "application/zip") {
        return false;
    }
    if (ct && ct->name().endsWith(QLatin1String("pkpass"))) {
        return true;
    }
    const auto cd = content->contentDisposition(false);
    return cd && cd->filename().endsWith(QLatin1String("pkpass"));
}

namespace
{
class Formatter : public MessageViewer::MessagePartRendererBase
{
public:
    bool render(const MimeTreeParser::MessagePartPtr &msgPart, MessageViewer::HtmlWriter *htmlWriter, MessageViewer::RenderContext *context) const override
    {
        Q_UNUSED(context)
        auto mp = msgPart.dynamicCast<MimeTreeParser::AttachmentMessagePart>();
        if (!mp || context->isHiddenHint(msgPart) || !msgPart->content() || !isPkPassContent(msgPart->content())) {
            return false;
        }

        std::unique_ptr<KPkPass::Pass> pass(KPkPass::Pass::fromData(msgPart->content()->decodedContent()));
        if (!pass) {
            return false;
        }
        const auto dir = mp->nodeHelper()->createTempDir(QStringLiteral("pkpass"));
        const auto logo = pass->logo();
        if (!logo.isNull()) {
            const QString fileName = dir + QStringLiteral("/logo.png");
            logo.save(fileName);
            pass->setProperty("logoUrl", QUrl::fromLocalFile(fileName));
            mp->nodeHelper()->addTempFile(fileName);
        }
        const auto strip = pass->strip();
        if (!strip.isNull()) {
            const QString fileName = dir + QStringLiteral("/strip.png");
            strip.save(fileName);
            pass->setProperty("stripUrl", QUrl::fromLocalFile(fileName));
            mp->nodeHelper()->addTempFile(fileName);
        }
        const auto background = pass->background();
        if (!background.isNull()) {
            const QString fileName = dir + QStringLiteral("/background.png");
            background.save(fileName);
            pass->setProperty("backgroundUrl", QUrl::fromLocalFile(fileName));
            mp->nodeHelper()->addTempFile(fileName);
        }
        const auto footer = pass->footer();
        if (!footer.isNull()) {
            const QString fileName = dir + QStringLiteral("/footer.png");
            footer.save(fileName);
            pass->setProperty("footerUrl", QUrl::fromLocalFile(fileName));
            mp->nodeHelper()->addTempFile(fileName);
        }
        const auto thumbnail = pass->thumbnail();
        if (!thumbnail.isNull()) {
            const QString fileName = dir + QStringLiteral("/thumbnail.png");
            thumbnail.save(fileName);
            pass->setProperty("thumbnailUrl", QUrl::fromLocalFile(fileName));
            mp->nodeHelper()->addTempFile(fileName);
        }

        const auto barcodes = pass->barcodes();
        if (!barcodes.isEmpty()) {
            const auto barcode = barcodes.at(0);
            std::unique_ptr<Prison::AbstractBarcode> code;
            switch (barcode.format()) {
            case KPkPass::Barcode::QR:
                code.reset(Prison::createBarcode(Prison::QRCode));
                break;
            case KPkPass::Barcode::Aztec:
                code.reset(Prison::createBarcode(Prison::Aztec));
                break;
            case KPkPass::Barcode::PDF417:
                code.reset(Prison::createBarcode(Prison::PDF417));
                break;
            case KPkPass::Barcode::Code128:
                code.reset(Prison::createBarcode(Prison::Code128));
                break;
            default:
                break;
            }

            if (code) {
                code->setData(barcode.message());

                const QString fileName = dir + QStringLiteral("/barcode.png");
                code->toImage(code->preferredSize(qGuiApp->devicePixelRatio())).save(fileName);

                pass->setProperty("barcodeUrl", QUrl::fromLocalFile(fileName));
                mp->nodeHelper()->addTempFile(fileName);
            }
        }

        // Grantlee can't handle QColor...
        if (pass->foregroundColor().isValid()) {
            pass->setProperty("foregroundColorName", pass->foregroundColor().name());
        }
        if (pass->backgroundColor().isValid()) {
            pass->setProperty("backgroundColorName", pass->backgroundColor().name());
        }
        if (pass->labelColor().isValid()) {
            pass->setProperty("labelColorName", pass->labelColor().name());
        }

        auto c = MessageViewer::MessagePartRendererManager::self()->createContext();
        c.insert(QStringLiteral("block"), mp.data());
        c.insert(QStringLiteral("pass"), pass.get());
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        Grantlee::Template t;
#else
        KTextTemplate::Template t;
#endif
        if (qobject_cast<KPkPass::BoardingPass *>(pass.get())) {
            t = MessageViewer::MessagePartRendererManager::self()->loadByName(QStringLiteral("org.kde.messageviewer/pkpass/boardingpass.html"));
        } else if (pass->type() == KPkPass::Pass::EventTicket) {
            t = MessageViewer::MessagePartRendererManager::self()->loadByName(QStringLiteral("org.kde.messageviewer/pkpass/eventticket.html"));
        } else if (pass->type() == KPkPass::Pass::Generic) {
            t = MessageViewer::MessagePartRendererManager::self()->loadByName(QStringLiteral("org.kde.messageviewer/pkpass/generic.html"));
        } else {
            // unknown pass type we have no template for
            return false;
        }
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        Grantlee::OutputStream s(htmlWriter->stream());
#else
        KTextTemplate::OutputStream s(htmlWriter->stream());
#endif
        t->render(&s, &c);
        return true;
    }
};

class Plugin : public QObject, public MessageViewer::MessagePartRenderPlugin
{
    Q_OBJECT
    Q_INTERFACES(MessageViewer::MessagePartRenderPlugin)
    Q_PLUGIN_METADATA(IID "com.kde.messageviewer.bodypartformatter" FILE "pkpass_plugin.json")
public:
    explicit Plugin(QObject *parent = nullptr)
        : QObject(parent)
    {
    }

    MessageViewer::MessagePartRendererBase *renderer(int index) override
    {
        return index == 0 ? new Formatter() : nullptr;
    }
};
}

#include "pkpass_plugin.moc"
