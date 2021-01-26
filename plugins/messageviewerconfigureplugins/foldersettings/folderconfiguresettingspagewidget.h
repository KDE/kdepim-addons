/*
   SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLDERCONFIGURESETTINGSPAGEWIDGET_H
#define FOLDERCONFIGURESETTINGSPAGEWIDGET_H

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
    FolderConfigureSettingsExperyWidget *mCollectionExpiryWidget = nullptr;
    FolderConfigureSettingsGeneralWidget *mFolderConfigureSettingsGeneralWidget = nullptr;
    FolderConfigureSettingsTemplateWidget *mCollectionTemplateWidget = nullptr;
    FolderConfigureSettingsViewWidget *mFolderConfigureSettingsViewWidget = nullptr;
};

#endif // FOLDERCONFIGURESETTINGSPAGEWIDGET_H
