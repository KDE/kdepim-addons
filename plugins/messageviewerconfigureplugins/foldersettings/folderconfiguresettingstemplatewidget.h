/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLDERCONFIGURESETTINGSTEMPLATEWIDGET_H
#define FOLDERCONFIGURESETTINGSTEMPLATEWIDGET_H

#include <QWidget>
#include <AkonadiCore/Collection>
namespace MailCommon {
class CollectionTemplatesWidget;
}
class FolderConfigureSettingsTemplateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FolderConfigureSettingsTemplateWidget(QWidget *parent = nullptr);
    ~FolderConfigureSettingsTemplateWidget();
    void save(Akonadi::Collection &col);
private:
    MailCommon::CollectionTemplatesWidget *mCollectionTemplateWidget = nullptr;
};

#endif // FOLDERCONFIGURESETTINGSTEMPLATEWIDGET_H
