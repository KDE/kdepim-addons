/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINCREATETODOTEST_H
#define VIEWERPLUGINCREATETODOTEST_H

#include <QObject>

class ViewerPluginCreateTodoTest : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginCreateTodoTest(QObject *parent = nullptr);
    ~ViewerPluginCreateTodoTest();

private Q_SLOTS:
    void shouldCreateAction();
    void shouldShowWidget();
};

#endif // VIEWERPLUGINCREATETODOTEST_H
