/*
   Copyright (C) 2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "diffhighlighter.h"
#include <KSyntaxHighlighting/Format>
#include <KSyntaxHighlighting/Theme>
#include <KSyntaxHighlighting/State>
#include <QPalette>

DiffHighlighter::DiffHighlighter()
{
    mDef = mRepo.definitionForName(QStringLiteral("Diff"));
    setDefinition(mDef);

    setTheme(/*(palette().color(QPalette::Base).lightness() < 128)
                 ? mRepo.defaultTheme(KSyntaxHighlighting::Repository::DarkTheme)*/
                 /*:*/ mRepo.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));
}

DiffHighlighter::~DiffHighlighter()
{

}

void DiffHighlighter::highlightDiff(const QString &str)
{
    mOutputDiff.clear();

    static const QLatin1String tableStyle(
        "style=\""
        "text-align: left; "
        "border: solid black 1px; "
        "padding: 0.5em; "
        "margin: 0em;\"");

    mOutputDiff = QStringLiteral("<br><div align=\"center\">");
    mOutputDiff += QLatin1String("<pre ") + tableStyle + QLatin1Char('>');

    KSyntaxHighlighting::State state;
    const QStringList lines = str.split(QLatin1Char('\n'));
    QStringList::ConstIterator end(lines.end());
    for (QStringList::ConstIterator it = lines.begin(); it != end; ++it) {
        mCurrentLine = (*it);
        state = highlightLine((*it), state);
        mOutputDiff += QLatin1Char('\n');
    }

    mOutputDiff += QLatin1String("</pre></div>");
}

void DiffHighlighter::applyFormat(int offset, int length, const KSyntaxHighlighting::Format &format)
{
    if (!format.isDefaultTextStyle(theme())) {
        mOutputDiff += QStringLiteral("<span style=\"");
        if (format.hasTextColor(theme()))
            mOutputDiff += QStringLiteral("color:") + format.textColor(theme()).name() + QStringLiteral(";");
        if (format.hasBackgroundColor(theme()))
            mOutputDiff += QStringLiteral("background-color:") + format.backgroundColor(theme()).name() + QStringLiteral(";");
        if (format.isBold(theme()))
            mOutputDiff += QStringLiteral("font-weight:bold;");
        if (format.isItalic(theme()))
            mOutputDiff += QStringLiteral("font-style:italic;");
        if (format.isUnderline(theme()))
            mOutputDiff += QStringLiteral("text-decoration:underline;");
        if (format.isStrikeThrough(theme()))
            mOutputDiff += QStringLiteral("text-decoration:line-through;");
        mOutputDiff += QStringLiteral("\">");
    }

    mOutputDiff += mCurrentLine.mid(offset, length).toHtmlEscaped();

    if (!format.isDefaultTextStyle(theme())) {
        mOutputDiff += QStringLiteral("</span>");
    }
}

QString DiffHighlighter::outputDiff() const
{
    return mOutputDiff;
}
