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

QString AdblockFilter::name() const
{
    return mName;
}

void AdblockFilter::setName(const QString &newName)
{
    mName = newName;
}

QDebug operator<<(QDebug d, const AdblockFilter &t)
{
    d << " url " << t.url();
    d << " name " << t.name();
    return d;
}
