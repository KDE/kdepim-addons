/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef STANDARDSHEADERSTYLEPLUGINTEST_H
#define STANDARDSHEADERSTYLEPLUGINTEST_H

#include <QObject>

class StandardsHeaderStylePluginTest : public QObject
{
    Q_OBJECT
public:
    explicit StandardsHeaderStylePluginTest(QObject *parent = nullptr);
    ~StandardsHeaderStylePluginTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldCreateInterface();
};

#endif // STANDARDSHEADERSTYLEPLUGINTEST_H
