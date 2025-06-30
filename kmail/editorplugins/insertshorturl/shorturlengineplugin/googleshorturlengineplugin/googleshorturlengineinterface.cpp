/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "googleshorturlengineinterface.h"
using namespace Qt::Literals::StringLiterals;

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
    return u"googleshorturl"_s;
}
