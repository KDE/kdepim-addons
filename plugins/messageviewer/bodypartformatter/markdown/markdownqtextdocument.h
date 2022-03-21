/*
   SPDX-FileCopyrightText: 2020-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "markdownabstract.h"

class MarkdownQTextDocument : public MarkdownAbstract
{
public:
    MarkdownQTextDocument();
    ~MarkdownQTextDocument() override;
    Q_REQUIRED_RESULT QString toHtml() const override;
};
