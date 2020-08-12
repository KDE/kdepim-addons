/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINMANAGERTEST_H
#define VIEWERPLUGINMANAGERTEST_H

#include <QObject>

class ViewerPluginManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginManagerTest(QObject *parent = nullptr);
    ~ViewerPluginManagerTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // VIEWERPLUGINMANAGERTEST_H
