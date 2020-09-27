/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLDERCONFIGURESETTINGSPAGEWIDGET_H
#define FOLDERCONFIGURESETTINGSPAGEWIDGET_H

#include <QWidget>
#include "folderconfiguresettings_private_export.h"
#include <AkonadiCore/Collection>
class FolderConfigureSettingsGeneralWidget;
class FolderConfigureSettingsTemplateWidget;
class FolderConfigureSettingsViewWidget;
class FolderConfigureSettingsExperyWidget;
class LIBFOLDERCONFIGURESETTINGS_TESTS_EXPORT FolderConfigureSettingsPageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FolderConfigureSettingsPageWidget(QWidget *parent = nullptr);
    ~FolderConfigureSettingsPageWidget();

    void save(const Akonadi::Collection::List &cols);
private:
    FolderConfigureSettingsExperyWidget *mCollectionExpiryWidget = nullptr;
    FolderConfigureSettingsGeneralWidget *mFolderConfigureSettingsGeneralWidget = nullptr;
    FolderConfigureSettingsTemplateWidget *mCollectionTemplateWidget = nullptr;
    FolderConfigureSettingsViewWidget *mFolderConfigureSettingsViewWidget = nullptr;
};

#endif // FOLDERCONFIGURESETTINGSPAGEWIDGET_H
