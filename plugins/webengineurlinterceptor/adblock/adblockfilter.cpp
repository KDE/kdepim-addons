/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfilter.h"

AdblockFilter::AdblockFilter()
{
}

AdblockFilter::~AdblockFilter() = default;

QString AdblockFilter::url() const
{
    return mUrl;
}

void AdblockFilter::setUrl(const QString &newUrl)
{
    mUrl = newUrl;
}
