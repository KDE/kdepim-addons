/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownabstract.h"

MarkdownAbstract::MarkdownAbstract()
{

}

MarkdownAbstract::~MarkdownAbstract()
{

}

void MarkdownAbstract::setText(const QString &str)
{
    mText = str;
}
