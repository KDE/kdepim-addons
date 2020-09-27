/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLDERCONFIGURESETTINGSVIEWWIDGET_H
#define FOLDERCONFIGURESETTINGSVIEWWIDGET_H

#include "folderconfiguresettingspagebase.h"

#include <QWidget>
#include <AkonadiCore/Collection>
namespace MailCommon {
class CollectionViewWidget;
}
class FolderConfigureSettingsViewWidget : public FolderConfigureSettingsPageBase
{
    Q_OBJECT
public:
    explicit FolderConfigureSettingsViewWidget(QWidget *parent = nullptr);
    ~FolderConfigureSettingsViewWidget();
    void save(Akonadi::Collection &col);
private:
    MailCommon::CollectionViewWidget *mCollectionViewWidget = nullptr;
};

#endif // FOLDERCONFIGURESETTINGSVIEWWIDGET_H
