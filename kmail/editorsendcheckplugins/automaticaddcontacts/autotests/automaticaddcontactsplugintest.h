/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef AUTOMATICADDCONTACTSPLUGINTEST_H
#define AUTOMATICADDCONTACTSPLUGINTEST_H

#include <QObject>

class AutomaticAddContactsPluginTest : public QObject
{
    Q_OBJECT
public:
    explicit AutomaticAddContactsPluginTest(QObject *parent = nullptr);
    ~AutomaticAddContactsPluginTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // AUTOMATICADDCONTACTSPLUGINTEST_H
