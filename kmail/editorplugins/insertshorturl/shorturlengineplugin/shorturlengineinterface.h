/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
    QNetworkAccessManager *const mNetworkAccessManager;
    ShortUrlEnginePlugin *const mEnginePlugin;
};
#endif // SHORTURLENGINEINTERFACE_H
