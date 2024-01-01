/*
   SPDX-FileCopyrightText: 2020-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "folderconfiguresettingspagebase.h"

#include <Akonadi/Collection>
class QWidget;
namespace MailCommon
{
class CollectionViewWidget;
}
class FolderConfigureSettingsViewWidget : public FolderConfigureSettingsPageBase
{
    Q_OBJECT
public:
    explicit FolderConfigureSettingsViewWidget(QWidget *parent = nullptr);
    ~FolderConfigureSettingsViewWidget() override;
    void save(Akonadi::Collection &col);

private:
    MailCommon::CollectionViewWidget *const mCollectionViewWidget;
};
