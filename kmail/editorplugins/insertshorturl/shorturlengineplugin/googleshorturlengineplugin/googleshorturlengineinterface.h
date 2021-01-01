/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GOOGLESHORTURLENGINEINTERFACE_H
#define GOOGLESHORTURLENGINEINTERFACE_H

#include <pimcommon/shorturlengineinterface.h>

class GoogleShortUrlEngineInterface : public ShortUrlEngineInterface
{
public:
    explicit GoogleShortUrlEngineInterface(QObject *parent = nullptr);
    ~GoogleShortUrlEngineInterface() override;

    void generateShortUrl() override;
    QString engineName() const override;
};

#endif
