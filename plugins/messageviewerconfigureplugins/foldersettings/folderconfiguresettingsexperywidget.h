/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/


#ifndef FOLDERCONFIGURESETTINGSEXPERYWIDGET_H
#define FOLDERCONFIGURESETTINGSEXPERYWIDGET_H

#include "folderconfiguresettingspagebase.h"
#include <AkonadiCore/Collection>
namespace MailCommon {
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

#endif // FOLDERCONFIGURESETTINGSEXPERYWIDGET_H
