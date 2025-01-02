/*
   SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "folderconfiguresettings_private_export.h"
#include <Akonadi/Collection>
#include <QWidget>
class FolderSettingFilterProxyModel;
namespace MailCommon
{
class FolderTreeWidget;
}
class QPushButton;
class LIBFOLDERCONFIGURESETTINGS_TESTS_EXPORT FolderConfigureTreeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FolderConfigureTreeWidget(QWidget *parent = nullptr);
    ~FolderConfigureTreeWidget() override;
    [[nodiscard]] Akonadi::Collection::List listCollections() const;

private:
    LIBFOLDERCONFIGURESETTINGS_NO_EXPORT void changeFolderSelection(bool select);
    LIBFOLDERCONFIGURESETTINGS_NO_EXPORT void slotSelectionChanged();
    FolderSettingFilterProxyModel *const mFolderSettingFilterProxyModel;
    MailCommon::FolderTreeWidget *const mFolderTreeWidget;
    QPushButton *mSelectFolder = nullptr;
    QPushButton *mUnSelectFolder = nullptr;
};
