/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ANTIVIRUSPLUGININTERFACETEST_H
#define ANTIVIRUSPLUGININTERFACETEST_H

#include <QObject>

class AntiVirusPluginInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit AntiVirusPluginInterfaceTest(QObject *parent = nullptr);
    ~AntiVirusPluginInterfaceTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldCreateAction();
    void shouldEmitActivatedSignal();
};

#endif // AntiVirusPLUGININTERFACETEST_H
