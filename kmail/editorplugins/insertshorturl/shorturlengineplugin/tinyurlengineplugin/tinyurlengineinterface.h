/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef TINYURLENGINEINTERFACE_H
#define TINYURLENGINEINTERFACE_H

#include <../shorturlengineinterface.h>
#include <QNetworkReply>
class TinyUrlEngineInterface : public ShortUrlEngineInterface
{
    Q_OBJECT
public:
    explicit TinyUrlEngineInterface(ShortUrlEnginePlugin *plugin, QObject *parent = nullptr);
    ~TinyUrlEngineInterface() override;

    void generateShortUrl() override;

    QString engineName() const override;
private:
    void slotShortUrlFinished(QNetworkReply *reply);
    void slotErrorFound(QNetworkReply::NetworkError error);
};

#endif // TINYURLENGINEINTERFACE_H
