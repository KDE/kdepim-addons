/*
   SPDX-FileCopyrightText: 2020-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownqtextdocument.h"

#include <QTextDocument>

MarkdownQTextDocument::MarkdownQTextDocument()
{
}

MarkdownQTextDocument::~MarkdownQTextDocument()
{
}

QString MarkdownQTextDocument::toHtml() const
{
    QTextDocument textDocument;
    textDocument.setMarkdown(mText, QTextDocument::MarkdownNoHTML);
    const QString result = textDocument.toHtml();
    return result;
}
