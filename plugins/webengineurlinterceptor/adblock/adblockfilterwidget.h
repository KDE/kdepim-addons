/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "adblockplugin_private_export.h"
#include <QWidget>
class AdblockFilterListsView;
class QLineEdit;
class LIBADBLOCKPLUGIN_TESTS_EXPORT AdblockFilterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdblockFilterWidget(QWidget *parent = nullptr);
    ~AdblockFilterWidget() override;

private:
    AdblockFilterListsView *const mAdblockFilterListView;
    QLineEdit *const mSearchLineEdit;
};
