/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MARKDOWNPLUGINTEST_H
#define MARKDOWNPLUGINTEST_H

#include <QObject>

class MarkdownPluginTest : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownPluginTest(QObject *parent = nullptr);
    ~MarkdownPluginTest() override = default;
private Q_SLOTS:
    void shouldCreateInterface();
};

#endif // MARKDOWNPLUGINTEST_H
