/*
   SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MARKDOWNDISCOUNT_H
#define MARKDOWNDISCOUNT_H

#include "markdownabstract.h"

class MarkdownDiscount : public MarkdownAbstract
{
public:
    MarkdownDiscount();
    ~MarkdownDiscount() override;

    Q_REQUIRED_RESULT QString toHtml() const override;
};

#endif // MARKDOWNDISCOUNT_H
