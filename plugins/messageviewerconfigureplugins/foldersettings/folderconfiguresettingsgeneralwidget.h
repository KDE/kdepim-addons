/*
   SPDX-FileCopyrightText: 2020-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "folderconfiguresettings_private_export.h"
#include "folderconfiguresettingspagebase.h"
#include <Akonadi/Collection>
class QWidget;
namespace MailCommon
{
class CollectionGeneralWidget;
}
class LIBFOLDERCONFIGURESETTINGS_TESTS_EXPORT FolderConfigureSettingsGeneralWidget : public FolderConfigureSettingsPageBase
{
    Q_OBJECT
public:
    explicit FolderConfigureSettingsGeneralWidget(QWidget *parent = nullptr);
    ~FolderConfigureSettingsGeneralWidget() override;
    void save(Akonadi::Collection &col);

private:
    MailCommon::CollectionGeneralWidget *const mCollectionGeneralWidget;
};
