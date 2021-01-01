/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef TRIOPABSHORTURLENGINEINTERFACE_H
#define TRIOPABSHORTURLENGINEINTERFACE_H

#include "../../shorturlengineplugin/shorturlengineinterface.h"

class QNetworkReply;
class TripAbShortUrlEngineInterface : public ShortUrlEngineInterface
{
    Q_OBJECT
public:
    explicit TripAbShortUrlEngineInterface(ShortUrlEnginePlugin *plugin, QObject *parent = nullptr);
    ~TripAbShortUrlEngineInterface() override;

    void generateShortUrl() override;
    QString engineName() const override;

private:
    void slotShortUrlFinished(QNetworkReply *reply);
};

#endif
