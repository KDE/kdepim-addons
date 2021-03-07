/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef HEADERSTYLEPLUGINMANAGERTEST_H
#define HEADERSTYLEPLUGINMANAGERTEST_H

#include <QObject>

class HeaderStylePluginManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit HeaderStylePluginManagerTest(QObject *parent = nullptr);
    ~HeaderStylePluginManagerTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // HEADERSTYLEPLUGINMANAGERTEST_H
