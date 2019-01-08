/*
   Copyright (c) 2017 Volker Krause <vkrause@kde.org>

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

#include <MessageViewer/MessagePartRendererBase>
#include <MessageViewer/MessagePartRendererManager>
#include <MessageViewer/MessagePartRenderPlugin>

#include <MessageViewer/HtmlWriter>
#include <MimeTreeParser/MessagePart>

#include <KPkPass/BoardingPass>
#include <KPkPass/Barcode>

#include <grantlee/metatype.h>
#include <grantlee/template.h>

#include <prison/Prison>

#include <QUrl>
#include <QImage>
#include <QMetaProperty>

static bool isPkPassContent(KMime::Content *content)
{
    const auto ct = content->contentType(false);
    if (ct && ct->mimeType() == "application/vnd.apple.pkpass") {
        return true;
    }
    if (ct && ct->mimeType() != "application/octet-stream" && ct->mimeType() != "application/zip") {
        return false;
    }
    if (ct && ct->name().endsWith(QLatin1String("pkpass"))) {
        return true;
    }
    const auto cd = content->contentDisposition(false);
    return cd && cd->filename().endsWith(QLatin1String("pkpass"));
}

// Grantlee has no Q_GADGET support yet
#define GRANTLEE_MAKE_GADGET(Class) \
    GRANTLEE_BEGIN_LOOKUP(Class) \
    const auto idx = Class::staticMetaObject.indexOfProperty(property.toUtf8().constData()); \
    if (idx < 0) { \
        return {}; \
    } \
    const auto mp = Class::staticMetaObject.property(idx); \
    return mp.readOnGadget(&object); \
    GRANTLEE_END_LOOKUP

GRANTLEE_MAKE_GADGET(KPkPass::Barcode)
GRANTLEE_MAKE_GADGET(KPkPass::Field)

namespace {
class Formatter : public MessageViewer::MessagePartRendererBase
{
public:
    bool render(const MimeTreeParser::MessagePartPtr &msgPart, MessageViewer::HtmlWriter *htmlWriter, MessageViewer::RenderContext *context) const override
    {
        Q_UNUSED(context);
        auto mp = msgPart.dynamicCast<MimeTreeParser::AttachmentMessagePart>();
        if (!mp || context->isHiddenHint(msgPart) || !msgPart->content() || !isPkPassContent(msgPart->content())) {
            return false;
        }

        std::unique_ptr<KPkPass::Pass> pass(KPkPass::Pass::fromData(msgPart->content()->decodedContent()));
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
            default:
                break;
            }

            if (code) {
                code->setData(barcode.message());
                code->toImage(code->minimumSize()); // minimumSize is only available after we rendered once...

                const QString fileName = dir + QStringLiteral("/barcode.png");
                code->toImage(code->minimumSize()).save(fileName);

                pass->setProperty("barcodeUrl", QUrl::fromLocalFile(fileName));
                mp->nodeHelper()->addTempFile(fileName);
            }
        }

        // Grantlee can't handle QColor...
        pass->setProperty("foregroundColorName", pass->foregroundColor().name());
        pass->setProperty("backgroundColorName", pass->backgroundColor().name());
        pass->setProperty("labelColorName", pass->labelColor().name());

        auto c = MessageViewer::MessagePartRendererManager::self()->createContext();
        c.insert(QStringLiteral("block"), mp.data());
        c.insert(QStringLiteral("pass"), pass.get());

        Grantlee::Template t;
        if (qobject_cast<KPkPass::BoardingPass *>(pass.get())) {
            t = MessageViewer::MessagePartRendererManager::self()->loadByName(QStringLiteral(":/org.kde.messageviewer/pkpass/boardingpass.html"));
        } else if (pass->type() == KPkPass::Pass::EventTicket) {
            t = MessageViewer::MessagePartRendererManager::self()->loadByName(QStringLiteral(":/org.kde.messageviewer/pkpass/eventticket.html"));
        }

        Grantlee::OutputStream s(htmlWriter->stream());
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
        Grantlee::registerMetaType<KPkPass::Barcode>();
        Grantlee::registerMetaType<KPkPass::Field>();
    }

    MessageViewer::MessagePartRendererBase *renderer(int index) override
    {
        return index == 0 ? new Formatter() : nullptr;
    }
};
}

#include "pkpass_plugin.moc"
