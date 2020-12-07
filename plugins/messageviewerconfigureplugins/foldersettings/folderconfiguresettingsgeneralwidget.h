/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLDERCONFIGURESETTINGSGENERALWIDGET_H
#define FOLDERCONFIGURESETTINGSGENERALWIDGET_H

#include <QWidget>
#include "folderconfiguresettings_private_export.h"
#include "folderconfiguresettingspagebase.h"
#include <AkonadiCore/Collection>
namespace MailCommon {
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

#endif // FOLDERCONFIGURESETTINGSGENERALWIDGET_H
