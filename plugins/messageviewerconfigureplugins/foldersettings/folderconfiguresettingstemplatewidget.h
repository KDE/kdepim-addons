/*
   SPDX-FileCopyrightText: 2020-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "folderconfiguresettingspagebase.h"

#include <Akonadi/Collection>
class QWidget;
namespace MailCommon
{
class CollectionTemplatesWidget;
}
class FolderConfigureSettingsTemplateWidget : public FolderConfigureSettingsPageBase
{
    Q_OBJECT
public:
    explicit FolderConfigureSettingsTemplateWidget(QWidget *parent = nullptr);
    ~FolderConfigureSettingsTemplateWidget() override;
    void save(Akonadi::Collection &col);

private:
    MailCommon::CollectionTemplatesWidget *const mCollectionTemplateWidget;
};
