/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

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

    Q_REQUIRED_RESULT virtual QString toHtml() const = 0;

protected:
    QString mText;
};
