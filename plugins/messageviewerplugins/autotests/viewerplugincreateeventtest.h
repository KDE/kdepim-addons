/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINCREATEEVENTTEST_H
#define VIEWERPLUGINCREATEEVENTTEST_H

#include <QObject>

class ViewerPluginCreateeventTest : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginCreateeventTest(QObject *parent = nullptr);
    ~ViewerPluginCreateeventTest();

private Q_SLOTS:
    void shouldCreateAction();
    void shouldShowWidget();
};

#endif // VIEWERPLUGINCREATEEVENTTEST_H
