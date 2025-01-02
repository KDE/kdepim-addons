/*
   SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownabstract.h"

MarkdownAbstract::MarkdownAbstract() = default;

MarkdownAbstract::~MarkdownAbstract() = default;

void MarkdownAbstract::setText(const QString &str)
{
    mText = str;
}
