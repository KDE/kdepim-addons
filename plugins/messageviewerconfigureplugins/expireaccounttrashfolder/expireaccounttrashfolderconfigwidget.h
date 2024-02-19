/*
   SPDX-FileCopyrightText: 2020-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "expireaccounttrashfolderconfig_private_export.h"
#include <QWidget>
namespace MailCommon
{
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
    LIBEXPIREACCOUNTTRASHFOLDERCONFIG_NO_EXPORT void save(bool saveSettings, bool expireNow);
    LIBEXPIREACCOUNTTRASHFOLDERCONFIG_NO_EXPORT void slotSaveAndExpireRequested();
    MailCommon::CollectionExpiryWidget *const mCollectionExpiryWidget;
};
