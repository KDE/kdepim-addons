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

#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <KSyntaxHighlighting/AbstractHighlighter>

class QTextStream;

class Highlighter : public KSyntaxHighlighting::AbstractHighlighter
{
public:
    Highlighter(QTextStream *stream);
    ~Highlighter();

    void highlight(const QString &str);

protected:
    void applyFormat(int offset, int length, const KSyntaxHighlighting::Format &format) override;
private:
    QString mCurrentLine;
    QTextStream *mStream;
};

#endif // DIFFHIGHLIGHTER_H
