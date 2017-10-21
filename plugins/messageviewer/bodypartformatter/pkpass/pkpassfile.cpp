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

#include <KZip>
#include <prison/Prison>

#include <QBuffer>
#include <QDebug>
#include <QImage>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLocale>
#include <QTextCodec>

PkPassFile::PkPassFile(const QString &passType, QObject* parent)
    : QObject (parent)
    , m_passType(passType)
{
}

PkPassFile::~PkPassFile() = default;

QJsonObject PkPassFile::data() const
{
    return m_passObj;
}

QJsonObject PkPassFile::passData() const
{
    return m_passObj.value(m_passType).toObject();
}

QString PkPassFile::message(const QString& key) const
{
    const auto it = m_messages.constFind(key);
    if (it != m_messages.constEnd())
        return it.value();
    return key;
}

QString PkPassFile::backgroundColor() const
{
    return m_passObj.value(QLatin1String("backgroundColor")).toString();
}

QString PkPassFile::foregroundColor() const
{
    return m_passObj.value(QLatin1String("foregroundColor")).toString();
}

QString PkPassFile::labelColor() const
{
    const auto c = m_passObj.value(QLatin1String("labelColor")).toString();
    if (!c.isEmpty())
        return c;
    return foregroundColor();
}

QString PkPassFile::logoText() const
{
    return message(m_passObj.value(QLatin1String("logoText")).toString());
}

QImage PkPassFile::logo() const
{
    auto file = m_zip->directory()->file(QStringLiteral("logo.png"));
    if (!file)
        return {};
    std::unique_ptr<QIODevice> dev(file->createDevice());
    return QImage::fromData(dev->readAll());
}

QImage PkPassFile::barcode() const
{
    const auto barcodeData = data().value(QLatin1String("barcode")).toObject();
    const auto formatName = barcodeData.value(QLatin1String("format")).toString();
    const auto msg = barcodeData.value(QLatin1String("message")).toString();
    // TODO: consider messageEncoding, once Prison supports that
    if (formatName.isEmpty() || msg.isEmpty())
        return {};

    std::unique_ptr<Prison::AbstractBarcode> code;
    if (formatName == QLatin1String("PKBarcodeFormatQR"))
        code.reset(Prison::createBarcode(Prison::QRCode));
    else if (formatName == QLatin1String("PKBarcodeFormatPDF417"))
        {} // TODO
    else if (formatName == QLatin1String("PKBarcodeFormatAztec"))
        code.reset(Prison::createBarcode(Prison::Aztec));
    else if (formatName == QLatin1String("PKBarcodeFormatCode128"))
        {} // TODO

    if (!code)
        return {};
    code->setData(msg);
    return code->toImage(code->minimumSize() * 4);
}

QString PkPassFile::barcodeAltText() const
{
    return data().value(QLatin1String("barcode")).toObject().value(QLatin1String("altText")).toString();
}

QVector<PkPassField> PkPassFile::auxiliaryFields() const
{
    return fields(QLatin1String("auxiliaryFields"));
}

QVector<PkPassField> PkPassFile::backFields() const
{
    return fields(QLatin1String("backFields"));
}

QVector<PkPassField> PkPassFile::headerFields() const
{
    return fields(QLatin1String("headerFields"));
}

QVector<PkPassField> PkPassFile::primaryFields() const
{
    return fields(QLatin1String("primaryFields"));
}

QVector<PkPassField> PkPassFile::secondaryFields() const
{
    return fields(QLatin1String("secondaryFields"));
}

PkPassFile* PkPassFile::fromData(const QByteArray &data, QObject *parent)
{
    std::unique_ptr<QBuffer> buffer(new QBuffer);
    buffer->setData(data);
    buffer->open(QBuffer::ReadOnly);

    std::unique_ptr<KZip> zip(new KZip(buffer.get()));
    if (!zip->open(QIODevice::ReadOnly))
        return nullptr;

    // extract pass.json
    auto file = zip->directory()->file(QStringLiteral("pass.json"));
    if (!file)
        return nullptr;
    std::unique_ptr<QIODevice> dev(file->createDevice());
    const auto passObj = QJsonDocument::fromJson(dev->readAll()).object();

    PkPassFile *pass = nullptr;
    if (passObj.contains(QLatin1String("boardingPass")))
        pass = new PkPassBoardingPass(parent);
    // TODO: coupon, eventTicket, storeCard, generic
    else
        pass = new PkPassFile(QStringLiteral("generic"), parent);

    pass->m_buffer = std::move(buffer);
    pass->m_zip = std::move(zip);
    pass->m_passObj = passObj;
    pass->parse();
    return pass;
}

void PkPassFile::parse()
{
    // find the message catalog
    auto lang = QLocale().name();
    auto idx = lang.indexOf(QLatin1Char('_'));
    if (idx > 0)
        lang = lang.left(idx);
    lang += QLatin1String(".lproj");
    if (!parseMessages(lang))
        parseMessages(QStringLiteral("en.lproj"));
}

static int indexOfUnquoted(const QString &catalog, QLatin1Char c, int start)
{
    for (int i = start; i < catalog.size(); ++i) {
        if (catalog.at(i) == c)
            return i;
        if (catalog.at(i) == QLatin1Char('\\'))
            ++i;
    }

    return -1;
}

static QString unquote(const QStringRef &str)
{
    QString res;
    res.reserve(str.size());
    for (int i = 0; i < str.size(); ++i) {
        const auto c1 = str.at(i);
        if (c1 == QLatin1Char('\\') && i < str.size() - 1) {
            const auto c2 = str.at(i + 1);
            if (c2 == QLatin1Char('r')) {
                res.push_back(QLatin1Char('\r'));
            } else if (c2 == QLatin1Char('n')) {
                res.push_back(QLatin1Char('\n'));
            } else if (c2 == QLatin1Char('\\')) {
                res.push_back(c2);
            } else {
                res.push_back(c1);
                res.push_back(c2);
            }
            ++i;
        } else {
            res.push_back(c1);
        }
    }
    return res;
}

bool PkPassFile::parseMessages(const QString &lang)
{
    auto entry = m_zip->directory()->entry(lang);
    if (!entry || !entry->isDirectory())
        return false;

    auto dir = dynamic_cast<const KArchiveDirectory*>(entry);
    auto file = dir->file(QStringLiteral("pass.strings"));
    if (!file)
        return false;

    std::unique_ptr<QIODevice> dev(file->createDevice());
    auto codec = QTextCodec::codecForName("UTF-16BE");
    const auto catalog = codec->toUnicode(dev->readAll());

    int idx = 0;
    while (idx < catalog.size()) {
        // key
        const auto keyBegin = indexOfUnquoted(catalog, QLatin1Char('"'), idx) + 1;
        if (keyBegin < 1)
            break;
        const auto keyEnd = indexOfUnquoted(catalog, QLatin1Char('"'), keyBegin);
        if (keyEnd <= keyBegin)
            break;

        // value
        const auto valueBegin = indexOfUnquoted(catalog, QLatin1Char('"'), keyEnd + 2) + 1; // there's at least also the '='
        if (valueBegin <= keyEnd)
            break;
        const auto valueEnd = indexOfUnquoted(catalog, QLatin1Char('"'), valueBegin);
        if (valueEnd <= valueBegin)
            break;

        const auto key = catalog.mid(keyBegin, keyEnd - keyBegin);
        const auto value = unquote(catalog.midRef(valueBegin, valueEnd - valueBegin));
        m_messages.insert(key, value);
        idx = valueEnd + 1; // there's at least the linebreak and/or a ';'
    }

    return !m_messages.isEmpty();
}

QVector<PkPassField> PkPassFile::fields(const QLatin1String &fieldType) const
{
    const auto a = passData().value(fieldType).toArray();
    QVector<PkPassField> f;
    f.reserve(a.size());
    foreach (const auto &v, a)
        f.push_back(PkPassField{v.toObject(), this});
    return f;
}
