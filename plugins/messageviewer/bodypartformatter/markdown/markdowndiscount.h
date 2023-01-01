/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "markdownabstract.h"

class MarkdownDiscount : public MarkdownAbstract
{
public:
    MarkdownDiscount();
    ~MarkdownDiscount() override;

    Q_REQUIRED_RESULT QString toHtml() const override;
};
