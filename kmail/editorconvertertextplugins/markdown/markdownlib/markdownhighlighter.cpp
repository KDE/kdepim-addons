/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownhighlighter.h"
using namespace Qt::Literals::StringLiterals;

#include <KSyntaxHighlighting/Format>
#include <KSyntaxHighlighting/State>
#include <KSyntaxHighlighting/Theme>

#include <QTextStream>

MarkdownHighlighter::MarkdownHighlighter(QTextStream *stream)
    : mStream(stream)
{
}

MarkdownHighlighter::~MarkdownHighlighter() = default;

void MarkdownHighlighter::highlight(const QString &str)
{
    *mStream << u"<blockquote><pre>"_s;

    KSyntaxHighlighting::State state;

    int lineStart = 0;
    int lineEnd = str.indexOf(u'\n');

    for (; lineEnd != -1; lineStart = lineEnd + 1, lineEnd = str.indexOf(u'\n', lineStart)) {
        mCurrentLine = str.mid(lineStart, lineEnd - lineStart);
        state = highlightLine(mCurrentLine, state);
        *mStream << u'\n';
    }
    if (lineStart < str.size()) { // remaining content if str isn't ending with a newline
        mCurrentLine = str.mid(lineStart);
        state = highlightLine(mCurrentLine, state);
        *mStream << u'\n';
    }
    *mStream << QLatin1StringView("</pre></blockquote>\n");
}

void MarkdownHighlighter::applyFormat(int offset, int length, const KSyntaxHighlighting::Format &format)
{
    if (!format.isDefaultTextStyle(theme())) {
        *mStream << u"<span style=\""_s;
        if (format.hasTextColor(theme())) {
            *mStream << u"color:"_s << format.textColor(theme()).name() << u';';
        }
        if (format.hasBackgroundColor(theme())) {
            *mStream << u"background-color:"_s << format.backgroundColor(theme()).name() << u';';
        }
        if (format.isBold(theme())) {
            *mStream << u"font-weight:bold;"_s;
        }
        if (format.isItalic(theme())) {
            *mStream << u"font-style:italic;"_s;
        }
        if (format.isUnderline(theme())) {
            *mStream << u"text-decoration:underline;"_s;
        }
        if (format.isStrikeThrough(theme())) {
            *mStream << u"text-decoration:line-through;"_s;
        }
        *mStream << u"\">"_s;
    }

    *mStream << mCurrentLine.mid(offset, length).toHtmlEscaped();

    if (!format.isDefaultTextStyle(theme())) {
        *mStream << u"</span>"_s;
    }
}
