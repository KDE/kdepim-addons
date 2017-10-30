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

#ifndef PKPASSFILE_H
#define PKPASSFILE_H

#include "pkpassfield.h"

#include <QByteArray>
#include <QHash>
#include <QJsonObject>
#include <QObject>
#include <QVector>

#include <memory>

class KZip;
class QBuffer;
class QLatin1String;
class QString;

/** Base class for a pkpass file. */
class PkPassFile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString backgroundColor READ backgroundColor CONSTANT)
    Q_PROPERTY(QString foregroundColor READ foregroundColor CONSTANT)
    Q_PROPERTY(QString labelColor READ labelColor CONSTANT)
    Q_PROPERTY(QString logoText READ logoText CONSTANT)
    Q_PROPERTY(QString barcodeAltText READ barcodeAltText CONSTANT)

    Q_PROPERTY(QVector<PkPassField> auxiliaryFields READ auxiliaryFields CONSTANT)
    Q_PROPERTY(QVector<PkPassField> backFields READ backFields CONSTANT)
    Q_PROPERTY(QVector<PkPassField> headerFields READ headerFields CONSTANT)
    Q_PROPERTY(QVector<PkPassField> primaryFields READ primaryFields CONSTANT)
    Q_PROPERTY(QVector<PkPassField> secondaryFields READ secondaryFields CONSTANT)

public:
    ~PkPassFile();

    /** Content of the pass.json file. */
    QJsonObject data() const;
    /** The pass data structure of the pass.json file. */
    QJsonObject passData() const;
    /** Localized message for the given key. */
    QString message(const QString &key) const;

    QString backgroundColor() const;
    QString foregroundColor() const;
    QString labelColor() const;
    QString logoText() const;
    QImage logo() const;
    QImage barcode() const;
    QString barcodeAltText() const;

    QVector<PkPassField> auxiliaryFields() const;
    QVector<PkPassField> backFields() const;
    QVector<PkPassField> headerFields() const;
    QVector<PkPassField> primaryFields() const;
    QVector<PkPassField> secondaryFields() const;

    /** Create a appropriate sub-class based on the pkpass file type. */
    static PkPassFile *fromData(const QByteArray &data, QObject *parent = nullptr);

protected:
    explicit PkPassFile(const QString &passType, QObject *parent = nullptr);

private:
    void parse();
    bool parseMessages(const QString &lang);
    QVector<PkPassField> fields(const QLatin1String &fieldType) const;

    std::unique_ptr<QBuffer> m_buffer;
    std::unique_ptr<KZip> m_zip;
    QJsonObject m_passObj;
    QHash<QString, QString> m_messages;
    QString m_passType;
};

#endif // PKPASSFILE_H
