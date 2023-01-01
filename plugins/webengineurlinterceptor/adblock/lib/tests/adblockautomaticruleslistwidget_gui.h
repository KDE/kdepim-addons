/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>

class AdBlockAutomaticRulesListWidgetTest : public QWidget
{
    Q_OBJECT
public:
    explicit AdBlockAutomaticRulesListWidgetTest(const QString &fileName, QWidget *parent = nullptr);
    ~AdBlockAutomaticRulesListWidgetTest() override;
};
