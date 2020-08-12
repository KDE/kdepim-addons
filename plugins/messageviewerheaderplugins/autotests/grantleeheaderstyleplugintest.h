/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRANTLEEHEADERSTYLEPLUGINTEST_H
#define GRANTLEEHEADERSTYLEPLUGINTEST_H

#include <QObject>

class GrantleeHeaderStylePluginTest : public QObject
{
    Q_OBJECT
public:
    explicit GrantleeHeaderStylePluginTest(QObject *parent = nullptr);
    ~GrantleeHeaderStylePluginTest();

public Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldCreateInterface();
    void testThemeActivation_data();
    void testThemeActivation();
    void testThemeRender_data();
    void testThemeRender();

private:
    QString expectedDataLocation;
};

#endif // GRANTLEEHEADERSTYLEPLUGINTEST_H
