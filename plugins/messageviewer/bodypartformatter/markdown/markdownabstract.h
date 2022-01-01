/*
   SPDX-FileCopyrightText: 2020-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QString>

class MarkdownAbstract
{
public:
    MarkdownAbstract();
    virtual ~MarkdownAbstract();

    void setText(const QString &str);

    virtual Q_REQUIRED_RESULT QString toHtml() const = 0;

protected:
    QString mText;
};

