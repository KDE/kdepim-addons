/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINEXTERNALSCRIPTTEST_H
#define VIEWERPLUGINEXTERNALSCRIPTTEST_H

#include <QObject>

class ViewerPluginExternalscriptTest : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalscriptTest(QObject *parent = nullptr);
    ~ViewerPluginExternalscriptTest();
};

#endif // VIEWERPLUGINEXTERNALSCRIPTTEST_H
