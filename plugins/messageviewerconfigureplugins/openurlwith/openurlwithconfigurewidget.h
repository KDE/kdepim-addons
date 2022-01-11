/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>

class OpenUrlWithConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OpenUrlWithConfigureWidget(QWidget *parent = nullptr);
    ~OpenUrlWithConfigureWidget() override;
};
