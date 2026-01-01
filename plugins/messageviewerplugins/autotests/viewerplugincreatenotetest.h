/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ViewerPluginCreateNoteTest : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginCreateNoteTest(QObject *parent = nullptr);
    ~ViewerPluginCreateNoteTest() override;

private Q_SLOTS:
    void shouldCreateAction();
    void shouldShowWidget();
};
