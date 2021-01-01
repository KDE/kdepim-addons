/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef BRIEFHEADERSTYLEPLUGINTEST_H
#define BRIEFHEADERSTYLEPLUGINTEST_H

#include <QObject>

class BriefHeaderStylePluginTest : public QObject
{
    Q_OBJECT
public:
    explicit BriefHeaderStylePluginTest(QObject *parent = nullptr);
    ~BriefHeaderStylePluginTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldCreateInterface();
    void testFormatEmpty();
    void testFormat_data();
    void testFormat();
};

#endif // BRIEFHEADERSTYLEPLUGINTEST_H
