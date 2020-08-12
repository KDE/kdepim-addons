/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MARKDOWNCONFIGUREDIALOGTEST_H
#define MARKDOWNCONFIGUREDIALOGTEST_H

#include <QObject>

class MarkdownConfigureDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownConfigureDialogTest(QObject *parent = nullptr);
    ~MarkdownConfigureDialogTest() = default;
};

#endif // MARKDOWNCONFIGUREDIALOGTEST_H
