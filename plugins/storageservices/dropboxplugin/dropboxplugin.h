/*
    Copyright (c) 2015-2017 Montel Laurent <montel@kde.org>

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

#ifndef DROPBOXPLUGIN_H
#define DROPBOXPLUGIN_H

#include <pimcommon/storageserviceplugin.h>

#include <QVariant>

namespace PimCommon
{
class DropBoxPlugin : public PimCommon::StorageServicePlugin
{
    Q_OBJECT
public:
    explicit DropBoxPlugin(QObject *parent = Q_NULLPTR, const QList<QVariant> & = QList<QVariant>());
    ~DropBoxPlugin();

    QString storageServiceName() const Q_DECL_OVERRIDE;

    StorageServicePlugin::Capabilities capabilities() const Q_DECL_OVERRIDE;
    QString description() const Q_DECL_OVERRIDE;
    QUrl serviceUrl() const Q_DECL_OVERRIDE;

    QString dropboxOauthConsumerKey() const;
    QString dropboxOauthSignature() const;
    QString dropboxRootPath() const;
    QString disallowedSymbols() const Q_DECL_OVERRIDE;
    QString disallowedSymbolsStr() const Q_DECL_OVERRIDE;
    qlonglong maximumUploadFileSize() const Q_DECL_OVERRIDE;

    QIcon icon() const Q_DECL_OVERRIDE;
    PimCommon::StorageServiceInterface *createStorageService(const QString &identifier) Q_DECL_OVERRIDE;
};
}
#endif // DROPBOXPLUGIN_H
