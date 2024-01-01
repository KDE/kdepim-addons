/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class SelectImapWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit SelectImapWidgetTest(QObject *parent = nullptr);
    ~SelectImapWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAssignText();
};
