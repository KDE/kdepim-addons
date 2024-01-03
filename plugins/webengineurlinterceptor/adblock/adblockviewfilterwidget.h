/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>

class AdblockViewFilterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdblockViewFilterWidget(QWidget *parent = nullptr);
    ~AdblockViewFilterWidget() override;
};
