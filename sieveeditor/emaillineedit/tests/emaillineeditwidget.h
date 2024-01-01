/*
   SPDX-FileCopyrightText: 2018-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>
class EmailLineEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EmailLineEditWidget(QWidget *parent = nullptr);
    ~EmailLineEditWidget() override = default;
};
