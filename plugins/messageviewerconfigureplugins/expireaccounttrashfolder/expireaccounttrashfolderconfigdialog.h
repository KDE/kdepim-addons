/*
   SPDX-FileCopyrightText: 2020-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "libexpireaccounttrashfolderconfig_export.h"
#include <QDialog>
class ExpireAccountTrashFolderConfigWidget;
class LIBEXPIREACCOUNTTRASHFOLDERCONFIG_EXPORT ExpireAccountTrashFolderConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ExpireAccountTrashFolderConfigDialog(QWidget *parent = nullptr);
    ~ExpireAccountTrashFolderConfigDialog() override;

private:
    void writeConfig();
    void readConfig();
    ExpireAccountTrashFolderConfigWidget *const mExpireAccountTrashFolderConfig;
};
