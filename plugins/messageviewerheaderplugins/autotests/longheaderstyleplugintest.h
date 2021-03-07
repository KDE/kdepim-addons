/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LONGHEADERSTYLEPLUGINTEST_H
#define LONGHEADERSTYLEPLUGINTEST_H

#include <QObject>

class LongHeaderStylePluginTest : public QObject
{
    Q_OBJECT
public:
    explicit LongHeaderStylePluginTest(QObject *parent = nullptr);
    ~LongHeaderStylePluginTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldCreateInterface();
};

#endif // LONGHEADERSTYLEPLUGINTEST_H
