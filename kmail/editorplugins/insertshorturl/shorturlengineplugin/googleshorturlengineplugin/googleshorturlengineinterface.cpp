/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "googleshorturlengineinterface.h"

GoogleShortUrlEngineInterface::GoogleShortUrlEngineInterface(QObject *parent)
    : ShortUrlEngineInterface(parent)
{
}

GoogleShortUrlEngineInterface::~GoogleShortUrlEngineInterface()
{
}

void GoogleShortUrlEngineInterface::generateShortUrl()
{
}

QString GoogleShortUrlEngineInterface::engineName() const
{
    return QStringLiteral("googleshorturl");
}
