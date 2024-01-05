/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QTreeWidget>

class ScamConfigureSettingsTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ScamConfigureSettingsTreeWidget(QWidget *parent = nullptr);
    ~ScamConfigureSettingsTreeWidget() override;
};
