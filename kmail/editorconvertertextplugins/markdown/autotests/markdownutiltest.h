/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef MARKDOWNUTILTEST_H
#define MARKDOWNUTILTEST_H

#include <QObject>

class MarkdownUtilTest : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownUtilTest(QObject *parent = nullptr);
    ~MarkdownUtilTest() = default;
private Q_SLOTS:
    void shouldConvert();
    void shouldConvert_data();
};

#endif // MARKDOWNUTILTEST_H
