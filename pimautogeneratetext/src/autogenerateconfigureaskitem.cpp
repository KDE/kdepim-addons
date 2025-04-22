/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autogenerateconfigureaskitem.h"

AutogenerateConfigureAskItem::AutogenerateConfigureAskItem() = default;

AutogenerateConfigureAskItem::~AutogenerateConfigureAskItem() = default;

bool AutogenerateConfigureAskItem::enabled() const
{
    return mEnabled;
}

void AutogenerateConfigureAskItem::setEnabled(bool newEnabled)
{
    mEnabled = newEnabled;
}

QString AutogenerateConfigureAskItem::text() const
{
    return mText;
}

void AutogenerateConfigureAskItem::setText(const QString &newText)
{
    mText = newText;
}

QDebug operator<<(QDebug d, const AutogenerateConfigureAskItem &t)
{
    d.space() << "text:" << t.text();
    d.space() << "enabled:" << t.enabled();
    return d;
}
