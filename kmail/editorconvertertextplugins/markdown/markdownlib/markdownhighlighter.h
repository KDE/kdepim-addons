/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

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
