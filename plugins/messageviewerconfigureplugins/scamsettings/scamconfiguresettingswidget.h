/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>

class ScamConfigureSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScamConfigureSettingsWidget(QWidget *parent = nullptr);
    ~ScamConfigureSettingsWidget() override;
};
