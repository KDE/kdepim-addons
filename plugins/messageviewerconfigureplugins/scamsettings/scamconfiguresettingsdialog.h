/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>

class ScamConfigureSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ScamConfigureSettingsDialog(QWidget *parent = nullptr);
    ~ScamConfigureSettingsDialog() override;
};
