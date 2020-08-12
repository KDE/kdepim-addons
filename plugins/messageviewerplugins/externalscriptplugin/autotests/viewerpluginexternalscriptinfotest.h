/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINEXTERNALSCRIPTINFOTEST_H
#define VIEWERPLUGINEXTERNALSCRIPTINFOTEST_H

#include <QObject>

class ViewerPluginExternalScriptInfoTest : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalScriptInfoTest(QObject *parent = nullptr);
    ~ViewerPluginExternalScriptInfoTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldHaveValid();
    void shouldBeEqual_data();
    void shouldBeEqual();
};

#endif // VIEWERPLUGINEXTERNALSCRIPTINFOTEST_H
