/*
   SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "folderconfiguresettings_private_export.h"
#include <QWidget>
class FolderConfigureTreeWidget;
class FolderConfigureSettingsPageWidget;
class QSplitter;
class LIBFOLDERCONFIGURESETTINGS_TESTS_EXPORT FolderConfigureSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FolderConfigureSettingsWidget(QWidget *parent = nullptr);
    ~FolderConfigureSettingsWidget() override;
    void save();

private:
    LIBFOLDERCONFIGURESETTINGS_NO_EXPORT void readConfig();
    LIBFOLDERCONFIGURESETTINGS_NO_EXPORT void saveConfig();
    FolderConfigureTreeWidget *const mFolderConfigureTreeWidget;
    FolderConfigureSettingsPageWidget *const mFolderConfigureSettingsPageWidget;
    QSplitter *const mSplitter;
};
