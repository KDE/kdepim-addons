/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autogenerateconfigureaskinfo.h"
#include <QDebug>

AutogenerateConfigureAskInfo::AutogenerateConfigureAskInfo() = default;

AutogenerateConfigureAskInfo::~AutogenerateConfigureAskInfo() = default;

bool AutogenerateConfigureAskInfo::enabled() const
{
    return mEnabled;
}

void AutogenerateConfigureAskInfo::setEnabled(bool newEnabled)
{
    mEnabled = newEnabled;
}

QString AutogenerateConfigureAskInfo::text() const
{
    return mText;
}

void AutogenerateConfigureAskInfo::setText(const QString &newText)
{
    mText = newText;
}

QString AutogenerateConfigureAskInfo::title() const
{
    return mTitle;
}

void AutogenerateConfigureAskInfo::setTitle(const QString &newTitle)
{
    mTitle = newTitle;
}

bool AutogenerateConfigureAskInfo::operator==(const AutogenerateConfigureAskInfo &other) const
{
    return other.enabled() == enabled() && other.title() == title() && other.text() == text();
}

QDebug operator<<(QDebug d, const AutogenerateConfigureAskInfo &t)
{
    d.space() << "text:" << t.text();
    d.space() << "title:" << t.title();
    d.space() << "enabled:" << t.enabled();
    return d;
}
