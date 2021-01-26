/*
   SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLDERCONFIGURESETTINGSDIALOG_H
#define FOLDERCONFIGURESETTINGSDIALOG_H

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

#endif // FOLDERCONFIGURESETTINGSDIALOG_H
