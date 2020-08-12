/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ISGDSHORTURLENGINEINTERFACE_H
#define ISGDSHORTURLENGINEINTERFACE_H

#include <../shorturlengineinterface.h>

#include <QSslError>
class QNetworkReply;

class IsgdShortUrlEngineInterface : public ShortUrlEngineInterface
{
    Q_OBJECT
public:
    explicit IsgdShortUrlEngineInterface(ShortUrlEnginePlugin *plugin, QObject *parent = nullptr);
    ~IsgdShortUrlEngineInterface() override;

    void generateShortUrl() override;
    QString engineName() const override;

private:
    void slotSslErrors(QNetworkReply *reply, const QList<QSslError> &error);
    void slotShortUrlFinished(QNetworkReply *reply);
};

#endif
