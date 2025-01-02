/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "adblockplugin_private_export.h"
#include <KConfigGroup>
#include <QWidget>

class AdblockFilterTreeView;
class QLineEdit;

class LIBADBLOCKPLUGIN_TESTS_EXPORT AdblockFilterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdblockFilterWidget(QWidget *parent = nullptr);
    ~AdblockFilterWidget() override;

    void loadSettings();
    void saveSettings();

Q_SIGNALS:
    void settingsChanged();

private:
    AdblockFilterTreeView *const mAdblockFilterListView;
    QLineEdit *const mSearchLineEdit;
};
