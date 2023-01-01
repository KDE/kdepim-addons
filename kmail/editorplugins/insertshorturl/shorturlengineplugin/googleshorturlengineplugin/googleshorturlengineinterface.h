/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <pimcommon/shorturlengineinterface.h>

class GoogleShortUrlEngineInterface : public ShortUrlEngineInterface
{
public:
    explicit GoogleShortUrlEngineInterface(QObject *parent = nullptr);
    ~GoogleShortUrlEngineInterface() override;

    void generateShortUrl() override;
    QString engineName() const override;
};
