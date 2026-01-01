/*
   SPDX-FileCopyrightText: 2020-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownqtextdocument.h"

#include <QTextDocument>

MarkdownQTextDocument::MarkdownQTextDocument() = default;

MarkdownQTextDocument::~MarkdownQTextDocument() = default;

QString MarkdownQTextDocument::toHtml() const
{
    QTextDocument textDocument;
    textDocument.setMarkdown(mText, QTextDocument::MarkdownNoHTML);
    const QString result = textDocument.toHtml();
    return result;
}
