/*
   SPDX-FileCopyrightText: 2021-2024 Laurent Montel <montel@kde.org>

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
    LIBSCAMCONFIGURESETTINGS_NO_EXPORT void readConfig();
    LIBSCAMCONFIGURESETTINGS_NO_EXPORT void writeConfig();
    LIBSCAMCONFIGURESETTINGS_NO_EXPORT void slotAccepted();
    ScamConfigureSettingsWidget *const mScamConfigureSettingsWidget;
};
