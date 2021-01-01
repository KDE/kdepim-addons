/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MARKDOWNINTERFACETEST_H
#define MARKDOWNINTERFACETEST_H

#include <QObject>

class MarkdownInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownInterfaceTest(QObject *parent = nullptr);
    ~MarkdownInterfaceTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // MARKDOWNINTERFACETEST_H
