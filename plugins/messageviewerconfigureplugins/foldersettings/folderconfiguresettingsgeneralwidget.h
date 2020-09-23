/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLDERCONFIGURESETTINGSGENERALWIDGET_H
#define FOLDERCONFIGURESETTINGSGENERALWIDGET_H

#include <QWidget>
#include "folderconfiguresettings_private_export.h"
namespace MailCommon {
class CollectionGeneralWidget;
}
class LIBFOLDERCONFIGURESETTINGS_TESTS_EXPORT FolderConfigureSettingsGeneralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FolderConfigureSettingsGeneralWidget(QWidget *parent = nullptr);
    ~FolderConfigureSettingsGeneralWidget();
    void save();
private:
    MailCommon::CollectionGeneralWidget *mCollectionGeneralWidget = nullptr;
};

#endif // FOLDERCONFIGURESETTINGSGENERALWIDGET_H
