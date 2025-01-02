/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

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
