/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef UR1CASHORTURLENGINEINTERFACE_H
#define UR1CASHORTURLENGINEINTERFACE_H

#include "../shorturlengineinterface.h"

#include <QSslError>
class QNetworkReply;

class Ur1CaShortUrlEngineInterface : public ShortUrlEngineInterface
{
    Q_OBJECT
public:
    explicit Ur1CaShortUrlEngineInterface(ShortUrlEnginePlugin *plugin, QObject *parent = nullptr);
    ~Ur1CaShortUrlEngineInterface() override;

    void generateShortUrl() override;
    QString engineName() const override;

private:
    void slotShortUrlFinished(QNetworkReply *reply);
    void slotSslErrors(QNetworkReply *reply, const QList<QSslError> &error);
};

#endif
