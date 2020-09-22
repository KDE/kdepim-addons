/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLDERCONFIGURESETTINGSVIEWWIDGET_H
#define FOLDERCONFIGURESETTINGSVIEWWIDGET_H

#include <QWidget>
namespace MailCommon {
class CollectionViewWidget;
}
class FolderConfigureSettingsViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FolderConfigureSettingsViewWidget(QWidget *parent = nullptr);
    ~FolderConfigureSettingsViewWidget();
    void save();
private:
    MailCommon::CollectionViewWidget *mCollectionViewWidget = nullptr;
};

#endif // FOLDERCONFIGURESETTINGSVIEWWIDGET_H
