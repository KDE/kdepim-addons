/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QTreeView>

class ScamConfigureSettingsTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit ScamConfigureSettingsTreeView(QWidget *parent = nullptr);
    ~ScamConfigureSettingsTreeView() override;
};
