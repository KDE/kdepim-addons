/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ViewerPluginCreateTodoTest : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginCreateTodoTest(QObject *parent = nullptr);
    ~ViewerPluginCreateTodoTest() override;

private Q_SLOTS:
    void shouldCreateAction();
    void shouldShowWidget();
};
