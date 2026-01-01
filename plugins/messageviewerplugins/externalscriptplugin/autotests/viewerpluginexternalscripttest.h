/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ViewerPluginExternalscriptTest : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalscriptTest(QObject *parent = nullptr);
    ~ViewerPluginExternalscriptTest() override;
};
