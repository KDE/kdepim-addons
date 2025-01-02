/*
   SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "libfolderconfiguresettings_export.h"
#include <QDialog>
class FolderConfigureSettingsWidget;
class LIBFOLDERCONFIGURESETTINGS_EXPORT FolderConfigureSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FolderConfigureSettingsDialog(QWidget *parent = nullptr);
    ~FolderConfigureSettingsDialog() override;

private:
    LIBFOLDERCONFIGURESETTINGS_NO_EXPORT void slotSave();
    LIBFOLDERCONFIGURESETTINGS_NO_EXPORT void readConfig();
    LIBFOLDERCONFIGURESETTINGS_NO_EXPORT void writeConfig();
    FolderConfigureSettingsWidget *const mFolderConfigureSettingsWidget;
};
