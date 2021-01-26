/*
   SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLDERCONFIGURESETTINGSTEMPLATEWIDGET_H
#define FOLDERCONFIGURESETTINGSTEMPLATEWIDGET_H

#include "folderconfiguresettingspagebase.h"

#include <AkonadiCore/Collection>
#include <QWidget>
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

#endif // FOLDERCONFIGURESETTINGSTEMPLATEWIDGET_H
