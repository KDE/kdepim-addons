/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <KSyntaxHighlighting/AbstractHighlighter>

class QTextStream;

class Highlighter : public KSyntaxHighlighting::AbstractHighlighter
{
public:
    explicit Highlighter(QTextStream *stream);
    ~Highlighter() override;

    void highlight(const QString &str);

protected:
    void applyFormat(int offset, int length, const KSyntaxHighlighting::Format &format) override;
private:
    QString mCurrentLine;
    QTextStream *mStream;
};

#endif // DIFFHIGHLIGHTER_H
