/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

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
    void readConfig();
    void saveConfig();
    FolderConfigureTreeWidget *const mFolderConfigureTreeWidget;
    FolderConfigureSettingsPageWidget *const mFolderConfigureSettingsPageWidget;
    QSplitter *const mSplitter;
};
