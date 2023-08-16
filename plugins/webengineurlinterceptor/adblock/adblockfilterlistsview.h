/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QListView>

class AdblockFilterListsView : public QListView
{
    Q_OBJECT
public:
    explicit AdblockFilterListsView(QWidget *parent = nullptr);
    ~AdblockFilterListsView() override;
};
