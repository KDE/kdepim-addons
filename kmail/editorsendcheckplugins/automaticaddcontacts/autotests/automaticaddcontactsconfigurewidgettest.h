/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>
class AutomaticAddContactsConfigureWidget;
class AutomaticAddContactsConfigureWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit AutomaticAddContactsConfigureWidgetTest(QObject *parent = nullptr);
    ~AutomaticAddContactsConfigureWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};
