/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LOGACTIVITIESPLUGININTERFACETEST_H
#define LOGACTIVITIESPLUGININTERFACETEST_H

#include <QObject>

class LogActivitiesPluginInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit LogActivitiesPluginInterfaceTest(QObject *parent = nullptr);
    ~LogActivitiesPluginInterfaceTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldCreateAction();
    void shouldEmitActivatedSignal();
};

#endif // LogActivitiesPLUGININTERFACETEST_H
