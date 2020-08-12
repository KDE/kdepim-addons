/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MARKDOWNABSTRACT_H
#define MARKDOWNABSTRACT_H

#include <QString>

class MarkdownAbstract
{
public:
    MarkdownAbstract();
    virtual ~MarkdownAbstract();

    void setText(const QString &str);

    virtual QString toHtml() const = 0;
protected:
    QString mText;
};

#endif // MARKDOWNABSTRACT_H
