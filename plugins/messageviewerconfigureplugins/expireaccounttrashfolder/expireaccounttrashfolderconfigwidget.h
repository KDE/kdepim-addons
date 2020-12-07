/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef EXPIREACCOUNTTRASHFOLDERCONFIGWIDGET_H
#define EXPIREACCOUNTTRASHFOLDERCONFIGWIDGET_H

#include <QWidget>
#include "expireaccounttrashfolderconfig_private_export.h"
namespace MailCommon {
class CollectionExpiryWidget;
}
class LIBEXPIREACCOUNTTRASHFOLDERCONFIG_TESTS_EXPORT ExpireAccountTrashFolderConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ExpireAccountTrashFolderConfigWidget(QWidget *parent = nullptr);
    ~ExpireAccountTrashFolderConfigWidget() override;
    void save();
private:
    void save(bool saveSettings, bool expireNow);
    void slotSaveAndExpireRequested();
    MailCommon::CollectionExpiryWidget *const mCollectionExpiryWidget;
};

#endif // EXPIREACCOUNTTRASHFOLDERCONFIGWIDGET_H
