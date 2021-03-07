/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FANCYHEADERSTYLEPLUGINTEST_H
#define FANCYHEADERSTYLEPLUGINTEST_H

#include <QObject>

class FancyHeaderStylePluginTest : public QObject
{
    Q_OBJECT
public:
    explicit FancyHeaderStylePluginTest(QObject *parent = nullptr);
    ~FancyHeaderStylePluginTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldCreateInterface();
    void testFormatEmpty();
    void testFormat_data();
    void testFormat();
};

#endif // FANCYHEADERSTYLEPLUGINTEST_H
