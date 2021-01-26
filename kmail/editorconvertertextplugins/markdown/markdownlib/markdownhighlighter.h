/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MARKDOWNHighlighter_H
#define MARKDOWNHighlighter_H

#include <KSyntaxHighlighting/AbstractHighlighter>

class QTextStream;

class MarkdownHighlighter : public KSyntaxHighlighting::AbstractHighlighter
{
public:
    explicit MarkdownHighlighter(QTextStream *stream);
    ~MarkdownHighlighter() override;

    void highlight(const QString &str);

protected:
    void applyFormat(int offset, int length, const KSyntaxHighlighting::Format &format) override;

private:
    QString mCurrentLine;
    QTextStream *const mStream;
};

#endif // MARKDOWNHighlighter_H
