/*
   SPDX-FileCopyrightText: 2021-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "scamconfiguresettings_private_export.h"
#include <QWidget>
class QTreeWidget;
class LIBSCAMCONFIGURESETTINGS_TESTS_EXPORT ScamConfigureSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScamConfigureSettingsWidget(QWidget *parent = nullptr);
    ~ScamConfigureSettingsWidget() override;

    void loadSettings();
    void saveSettings();

private:
    QTreeWidget *const mTreeWidget;
};
