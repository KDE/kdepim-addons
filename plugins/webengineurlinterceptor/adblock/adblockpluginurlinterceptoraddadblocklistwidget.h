/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>

class AdblockPluginUrlInterceptorAddAdblockListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdblockPluginUrlInterceptorAddAdblockListWidget(QWidget *parent = nullptr);
    ~AdblockPluginUrlInterceptorAddAdblockListWidget() override;
};
