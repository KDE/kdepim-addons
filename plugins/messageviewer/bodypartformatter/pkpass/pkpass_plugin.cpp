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

#include "pkpassfile.h"
#include "pkpassboardingpass.h"

#include <MessageViewer/MessagePartRendererBase>
#include <MessageViewer/MessagePartRendererManager>
#include <MessageViewer/MessagePartRenderPlugin>

#include <MimeTreeParser/HtmlWriter>
#include <MimeTreeParser/MessagePart>

#include <grantlee/metatype.h>
#include <grantlee/template.h>

#include <QUrl>
#include <QImage>
#include <QMetaProperty>

// Grantlee has no Q_GADGET support yet
GRANTLEE_BEGIN_LOOKUP(PkPassField)
const auto idx = PkPassField::staticMetaObject.indexOfProperty(property.toUtf8().constData());
if (idx < 0) {
    return {};
}
const auto mp = PkPassField::staticMetaObject.property(idx);
return mp.readOnGadget(&object);
GRANTLEE_END_LOOKUP

namespace {
class Formatter : public MessageViewer::MessagePartRendererBase
{
public:
    bool render(const MimeTreeParser::MessagePartPtr &msgPart, MimeTreeParser::HtmlWriter *htmlWriter, MessageViewer::RenderContext *context) const override
    {
        Q_UNUSED(context);
        auto mp = msgPart.dynamicCast<MimeTreeParser::AttachmentMessagePart>();
        if (!mp || mp->isHidden()) {
            return false;
        }

        std::unique_ptr<PkPassFile> pass(PkPassFile::fromData(msgPart->content()->decodedContent()));
        if (!qobject_cast<PkPassBoardingPass *>(pass.get())) {
            return false; // only boarding passes implemented so far
        }
        const auto dir = mp->nodeHelper()->createTempDir(QStringLiteral("pkpass"));
        const auto logo = pass->logo();
        if (!logo.isNull()) {
            const auto fileName = dir + QStringLiteral("/logo.png");
            logo.save(fileName);
            pass->setProperty("logoUrl", QUrl::fromLocalFile(fileName));
            mp->nodeHelper()->addTempFile(fileName);
        }

        const auto barcode = pass->barcode();
        if (!barcode.isNull()) {
            const auto fileName = dir + QStringLiteral("/barcode.png");
            barcode.save(fileName);
            pass->setProperty("barcodeUrl", QUrl::fromLocalFile(fileName));
            mp->nodeHelper()->addTempFile(fileName);
        }

        auto c = MessageViewer::MessagePartRendererManager::self()->createContext();
        c.insert(QStringLiteral("block"), mp.data());
        c.insert(QStringLiteral("pass"), pass.get());
        auto t = MessageViewer::MessagePartRendererManager::self()->loadByName(QStringLiteral(":/org.kde.messageviewer/pkpass/boardingpass.html"));
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
        Grantlee::registerMetaType<PkPassField>();
    }

    MessageViewer::MessagePartRendererBase *renderer(int index) override
    {
        return index == 0 ? new Formatter() : nullptr;
    }
};
}

#include "pkpass_plugin.moc"
