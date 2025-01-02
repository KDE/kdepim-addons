/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "../shorturlengineinterface.h"
class QNetworkReply;
class TinyUrlEngineInterface : public ShortUrlEngineInterface
{
    Q_OBJECT
public:
    explicit TinyUrlEngineInterface(ShortUrlEnginePlugin *plugin, QObject *parent = nullptr);
    ~TinyUrlEngineInterface() override;

    void generateShortUrl() override;

    [[nodiscard]] QString engineName() const override;

private:
    void slotShortUrlFinished(QNetworkReply *reply);
    void slotErrorFound(QNetworkReply::NetworkError error);
};
