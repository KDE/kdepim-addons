/*
   Copyright (c) 2015-2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef SHORTURLENGINEINTERFACE_H
#define SHORTURLENGINEINTERFACE_H

#include <QObject>
#include <QNetworkReply>
#include <QTextCursor>
#include "shorturl_export.h"
class QNetworkAccessManager;
class ShortUrlEnginePlugin;
class SHORTURL_EXPORT ShortUrlEngineInterface : public QObject
{
    Q_OBJECT
public:
    explicit ShortUrlEngineInterface(ShortUrlEnginePlugin *plugin, QObject *parent = nullptr);
    ~ShortUrlEngineInterface();

    void setShortUrl(const QString &url);
    virtual void generateShortUrl() = 0;
    virtual QString engineName() const = 0;
    QString pluginName() const;

    void setTextCursor(const QTextCursor &cursor);
protected Q_SLOTS:
    void slotErrorFound(QNetworkReply::NetworkError error);

Q_SIGNALS:
    void shortUrlFailed(const QString &error);

protected:
    QString mOriginalUrl;
    QTextCursor mTextCursor;
    bool mErrorFound = false;
    QNetworkAccessManager *mNetworkAccessManager = nullptr;
    ShortUrlEnginePlugin *mEnginePlugin = nullptr;
};
#endif // SHORTURLENGINEINTERFACE_H
