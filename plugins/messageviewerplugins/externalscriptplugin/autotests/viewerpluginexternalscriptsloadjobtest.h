/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINEXTERNALSCRIPTSLOADJOBTEST_H
#define VIEWERPLUGINEXTERNALSCRIPTSLOADJOBTEST_H

#include <QObject>

class ViewerPluginExternalScriptsLoadJobTest : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalScriptsLoadJobTest(QObject *parent = nullptr);
    ~ViewerPluginExternalScriptsLoadJobTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldAssignDirectory();
    void shouldLoadDataInfo();
    void shouldNotLoadEmptyDesktop();
    void shouldNotLoadNoNameDesktop();
    void shouldLoadTwoDifferentDesktopFile();
    void shouldNotLoadTwoSameNameDesktopFile();
};

#endif // VIEWERPLUGINEXTERNALSCRIPTSLOADJOBTEST_H
