/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLDERCONFIGURESETTINGSDIALOG_H
#define FOLDERCONFIGURESETTINGSDIALOG_H

#include <QDialog>
#include "libfolderconfiguresettings_export.h"
class FolderConfigureSettingsWidget;
class LIBFOLDERCONFIGURESETTINGS_EXPORT FolderConfigureSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FolderConfigureSettingsDialog(QWidget *parent = nullptr);
    ~FolderConfigureSettingsDialog();

private:
    void slotSave();
    void readConfig();
    void writeConfig();
    FolderConfigureSettingsWidget *const mFolderConfigureSettingsWidget;
};

#endif // FOLDERCONFIGURESETTINGSDIALOG_H
