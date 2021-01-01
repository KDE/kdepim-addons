/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ANTISPAMPLUGININTERFACETEST_H
#define ANTISPAMPLUGININTERFACETEST_H

#include <QObject>

class AntiSpamPluginInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit AntiSpamPluginInterfaceTest(QObject *parent = nullptr);
    ~AntiSpamPluginInterfaceTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldCreateAction();
    void shouldEmitActivatedSignal();
};

#endif // ANTISPAMPLUGININTERFACETEST_H
