/*
   SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLDERCONFIGURETREEWIDGET_H
#define FOLDERCONFIGURETREEWIDGET_H

#include <QWidget>
#include "folderconfiguresettings_private_export.h"
#include <AkonadiCore/Collection>
class FolderSettingFilterProxyModel;
class LIBFOLDERCONFIGURESETTINGS_TESTS_EXPORT FolderConfigureTreeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FolderConfigureTreeWidget(QWidget *parent = nullptr);
    ~FolderConfigureTreeWidget() override;
    Q_REQUIRED_RESULT Akonadi::Collection::List listCollections() const;
private:
    FolderSettingFilterProxyModel *mFolderSettingFilterProxyModel = nullptr;
};

#endif // FOLDERCONFIGURETREEWIDGET_H
