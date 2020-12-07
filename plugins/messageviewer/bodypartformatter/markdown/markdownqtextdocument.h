/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MARKDOWNQTEXTDOCUMENT_H
#define MARKDOWNQTEXTDOCUMENT_H

#include "markdownabstract.h"

class MarkdownQTextDocument : public MarkdownAbstract
{
public:
    MarkdownQTextDocument();
    ~MarkdownQTextDocument() override;
    Q_REQUIRED_RESULT QString toHtml() const override;
};

#endif // MARKDOWNQTEXTDOCUMENT_H
