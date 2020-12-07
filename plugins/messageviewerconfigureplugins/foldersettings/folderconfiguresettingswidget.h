/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLDERCONFIGURESETTINGSWIDGET_H
#define FOLDERCONFIGURESETTINGSWIDGET_H

#include <QWidget>
#include "folderconfiguresettings_private_export.h"
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

#endif // FOLDERCONFIGURESETTINGSWIDGET_H
