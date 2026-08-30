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

#include <KTextTemplate/MetaType>
#include <KTextTemplate/Template>

#include <Prison/Barcode>

#include <QGuiApplication>
#include <QImage>
#include <QUrl>
using namespace Qt::Literals::StringLiterals;

static bool isPkPassContent(KMime::Content *content)
{
    const auto ct = content->contentType(KMime::CreatePolicy::DontCreate);
    const QByteArray mimetype = ct ? ct->mimeType() : QByteArray();
    if (mimetype == "application/vnd.apple.pkpass") {
        return true;
    }
    if (mimetype != "application/octet-stream" && mimetype != "application/zip") {
        return false;
    }
    if (ct && ct->name().endsWith("pkpass"_L1)) {
        return true;
    }
    const auto cd = content->contentDisposition(KMime::CreatePolicy::DontCreate);
    return cd && cd->filename().endsWith("pkpass"_L1);
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

        std::unique_ptr<KPkPass::Pass> pass(KPkPass::Pass::fromData(msgPart->content()->decodedBody()));
        if (!pass) {
            return false;
        }
        const auto dir = mp->nodeHelper()->createTempDir(u"pkpass"_s);
        const auto logo = pass->logo();
        if (!logo.isNull()) {
            const QString fileName = dir + u"/logo.png"_s;
            logo.save(fileName);
            pass->setProperty("logoUrl", QUrl::fromLocalFile(fileName));
            mp->nodeHelper()->addTempFile(fileName);
        }
        const auto strip = pass->strip();
        if (!strip.isNull()) {
            const QString fileName = dir + u"/strip.png"_s;
            strip.save(fileName);
            pass->setProperty("stripUrl", QUrl::fromLocalFile(fileName));
            mp->nodeHelper()->addTempFile(fileName);
        }
        const auto background = pass->background();
        if (!background.isNull()) {
            const QString fileName = dir + u"/background.png"_s;
            background.save(fileName);
            pass->setProperty("backgroundUrl", QUrl::fromLocalFile(fileName));
            mp->nodeHelper()->addTempFile(fileName);
        }
        const auto footer = pass->footer();
        if (!footer.isNull()) {
            const QString fileName = dir + u"/footer.png"_s;
            footer.save(fileName);
            pass->setProperty("footerUrl", QUrl::fromLocalFile(fileName));
            mp->nodeHelper()->addTempFile(fileName);
        }
        const auto thumbnail = pass->thumbnail();
        if (!thumbnail.isNull()) {
            const QString fileName = dir + u"/thumbnail.png"_s;
            thumbnail.save(fileName);
            pass->setProperty("thumbnailUrl", QUrl::fromLocalFile(fileName));
            mp->nodeHelper()->addTempFile(fileName);
        }

        const auto barcodes = pass->barcodes();
        if (!barcodes.isEmpty()) {
            const auto barcode = barcodes.at(0);
            std::optional<Prison::Barcode> code;
            switch (barcode.format()) {
            case KPkPass::Barcode::QR:
                code = Prison::Barcode::create(Prison::QRCode);
                break;
            case KPkPass::Barcode::Aztec:
                code = Prison::Barcode::create(Prison::Aztec);
                break;
            case KPkPass::Barcode::PDF417:
                code = Prison::Barcode::create(Prison::PDF417);
                break;
            case KPkPass::Barcode::Code128:
                code = Prison::Barcode::create(Prison::Code128);
                break;
            default:
                break;
            }

            if (code) {
                code->setData(barcode.message());

                const QString fileName = dir + u"/barcode.png"_s;

                // determine the closest to preferred barcode size that fits
                // within the pass and is an integer scale of the minimum size
                const auto maxWidth = 332 * qGuiApp->devicePixelRatio();
                auto size = code->preferredSize(qGuiApp->devicePixelRatio());
                if (size.width() > maxWidth) {
                    const auto minSize = code->minimumSize();
                    const auto w = std::max<int>(1, maxWidth / minSize.width()) * minSize.width();
                    const auto h =
                        code->dimensions() == Prison::Barcode::TwoDimensions ? std::max<int>(1, maxWidth / minSize.width()) * minSize.height() : size.height();
                    size = QSizeF(w, h);
                }
                code->toImage(size).save(fileName);

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
        c.insert(u"block"_s, mp.data());
        c.insert(u"pass"_s, pass.get());
        KTextTemplate::Template t;
        if (qobject_cast<KPkPass::BoardingPass *>(pass.get())) {
            t = MessageViewer::MessagePartRendererManager::self()->loadByName(u"org.kde.messageviewer/pkpass/boardingpass.html"_s);
        } else if (pass->type() == KPkPass::Pass::EventTicket) {
            t = MessageViewer::MessagePartRendererManager::self()->loadByName(u"org.kde.messageviewer/pkpass/eventticket.html"_s);
        } else if (pass->type() == KPkPass::Pass::Generic) {
            t = MessageViewer::MessagePartRendererManager::self()->loadByName(u"org.kde.messageviewer/pkpass/generic.html"_s);
        } else {
            // unknown pass type we have no template for
            return false;
        }
        KTextTemplate::OutputStream s(htmlWriter->stream());
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

    [[nodiscard]] std::unique_ptr<MessageViewer::MessagePartRendererBase> renderer(int index) override
    {
        return index == 0 ? std::make_unique<Formatter>() : nullptr;
    }
};
}

#include "pkpass_plugin.moc"
