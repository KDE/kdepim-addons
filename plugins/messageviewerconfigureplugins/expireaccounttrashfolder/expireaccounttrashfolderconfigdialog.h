/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef EXPIREACCOUNTTRASHFOLDERCONFIGDIALOG_H
#define EXPIREACCOUNTTRASHFOLDERCONFIGDIALOG_H

#include <QDialog>
#include "libexpireaccounttrashfolderconfig_export.h"
class ExpireAccountTrashFolderConfigWidget;
class LIBEXPIREACCOUNTTRASHFOLDERCONFIG_EXPORT ExpireAccountTrashFolderConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ExpireAccountTrashFolderConfigDialog(QWidget *parent = nullptr);
    ~ExpireAccountTrashFolderConfigDialog();

private:
    void writeConfig();
    void readConfig();
    ExpireAccountTrashFolderConfigWidget *mExpireAccountTrashFolderConfig = nullptr;
};

#endif // EXPIREACCOUNTTRASHFOLDERCONFIGDIALOG_H
