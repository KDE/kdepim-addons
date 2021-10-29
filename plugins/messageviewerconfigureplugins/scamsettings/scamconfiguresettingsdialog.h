/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "libscamconfiguresettings_export.h"
#include <QDialog>
class ScamConfigureSettingsWidget;
class LIBSCAMCONFIGURESETTINGS_EXPORT ScamConfigureSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ScamConfigureSettingsDialog(QWidget *parent = nullptr);
    ~ScamConfigureSettingsDialog() override;

private:
    void readConfig();
    void writeConfig();
    ScamConfigureSettingsWidget *const mScamConfigureSettingsWidget;
};
