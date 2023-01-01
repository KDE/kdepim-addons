/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

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
    void slotSave();
    void readConfig();
    void writeConfig();
    FolderConfigureSettingsWidget *const mFolderConfigureSettingsWidget;
};
