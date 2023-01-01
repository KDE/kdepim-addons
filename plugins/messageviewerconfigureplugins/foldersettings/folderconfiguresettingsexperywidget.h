/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "folderconfiguresettingspagebase.h"
#include <Akonadi/Collection>
namespace MailCommon
{
class CollectionExpiryWidget;
}
class FolderConfigureSettingsExperyWidget : public FolderConfigureSettingsPageBase
{
    Q_OBJECT
public:
    explicit FolderConfigureSettingsExperyWidget(QWidget *parent = nullptr);
    ~FolderConfigureSettingsExperyWidget() override;
    void save(Akonadi::Collection &col);

private:
    MailCommon::CollectionExpiryWidget *const mCollectionExpiryWidget;
};
