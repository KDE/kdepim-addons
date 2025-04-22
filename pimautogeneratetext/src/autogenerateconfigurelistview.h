/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QListView>

class AutogenerateConfigureListView : public QListView
{
    Q_OBJECT
public:
    explicit AutogenerateConfigureListView(QWidget *parent = nullptr);
    ~AutogenerateConfigureListView() override;
};
