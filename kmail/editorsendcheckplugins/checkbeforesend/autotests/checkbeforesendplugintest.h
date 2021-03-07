/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CHECKBEFORESENDPLUGINTEST_H
#define CHECKBEFORESENDPLUGINTEST_H

#include <QObject>

class CheckBeforeSendPluginTest : public QObject
{
    Q_OBJECT
public:
    explicit CheckBeforeSendPluginTest(QObject *parent = nullptr);
    ~CheckBeforeSendPluginTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // CHECKBEFORESENDPLUGINTEST_H
