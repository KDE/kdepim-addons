/*
   SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "folderconfiguresettings_private_export.h"
#include <AkonadiCore/Collection>
#include <QWidget>
class FolderConfigureSettingsGeneralWidget;
class FolderConfigureSettingsTemplateWidget;
class FolderConfigureSettingsViewWidget;
class FolderConfigureSettingsExperyWidget;
class LIBFOLDERCONFIGURESETTINGS_TESTS_EXPORT FolderConfigureSettingsPageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FolderConfigureSettingsPageWidget(QWidget *parent = nullptr);
    ~FolderConfigureSettingsPageWidget() override;

    void save(const Akonadi::Collection::List &cols);

private:
    FolderConfigureSettingsExperyWidget *const mCollectionExpiryWidget;
    FolderConfigureSettingsGeneralWidget *const mFolderConfigureSettingsGeneralWidget;
    FolderConfigureSettingsTemplateWidget *const mCollectionTemplateWidget;
    FolderConfigureSettingsViewWidget *const mFolderConfigureSettingsViewWidget;
};

