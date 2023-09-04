/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "adblockplugin_private_export.h"
#include <QListView>

class LIBADBLOCKPLUGIN_TESTS_EXPORT AdblockFilterListsView : public QListView
{
    Q_OBJECT
public:
    explicit AdblockFilterListsView(QWidget *parent = nullptr);
    ~AdblockFilterListsView() override;
};
