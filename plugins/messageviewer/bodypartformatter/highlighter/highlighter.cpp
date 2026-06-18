/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "highlighter.h"

#include <KSyntaxHighlighting/Format>
#include <KSyntaxHighlighting/State>
#include <KSyntaxHighlighting/Theme>

#include <QTextStream>
using namespace Qt::Literals::StringLiterals;
Highlighter::Highlighter(QTextStream *stream)
    : mStream(stream)
{
}

Highlighter::~Highlighter() = default;

void Highlighter::highlight(const QString &str)
{
    *mStream << QStringLiteral("<pre class=\"highlightattachment\">");

    KSyntaxHighlighting::State state;

    int lineStart = 0;
    int lineEnd = str.indexOf(QLatin1Char('\n'));

    for (; lineEnd != -1; lineStart = lineEnd + 1, lineEnd = str.indexOf(QLatin1Char('\n'), lineStart)) {
        mCurrentLine = str.mid(lineStart, lineEnd - lineStart);
        state = highlightLine(mCurrentLine, state);
        *mStream << QLatin1Char('\n');
    }
    if (lineStart < str.size()) { // remaining content if str isn't ending with a newline
        mCurrentLine = str.mid(lineStart);
        state = highlightLine(mCurrentLine, state);
        *mStream << QLatin1Char('\n');
    }
    *mStream << QLatin1StringView("</pre>\n");
}

void Highlighter::applyFormat(int offset, int length, const KSyntaxHighlighting::Format &format)
{
    if (!format.isDefaultTextStyle(theme())) {
        *mStream << QStringLiteral("<span style=\"");
        if (format.hasTextColor(theme())) {
            *mStream << QStringLiteral("color:") << format.textColor(theme()).name() << QLatin1Char(';');
        }
        if (format.hasBackgroundColor(theme())) {
            *mStream << QStringLiteral("background-color:") << format.backgroundColor(theme()).name() << QLatin1Char(';');
        }
        if (format.isBold(theme())) {
            *mStream << QStringLiteral("font-weight:bold;");
        }
        if (format.isItalic(theme())) {
            *mStream << QStringLiteral("font-style:italic;");
        }
        const bool hasUnderline = format.isUnderline(theme());
        const bool hasStrikeThrough = format.isStrikeThrough(theme());
        if (hasUnderline || hasStrikeThrough) {
            *mStream << u"text-decoration:"_s;
            if (hasUnderline) {
                *mStream << u"underline"_s;
            }
            if (hasUnderline && hasStrikeThrough) {
                *mStream << u' ';
            }
            if (hasStrikeThrough) {
                *mStream << u"line-through"_s;
            }
            *mStream << u';';
        }
        *mStream << QStringLiteral("\">");
    }

    *mStream << mCurrentLine.mid(offset, length).toHtmlEscaped();

    if (!format.isDefaultTextStyle(theme())) {
        *mStream << QStringLiteral("</span>");
    }
}
