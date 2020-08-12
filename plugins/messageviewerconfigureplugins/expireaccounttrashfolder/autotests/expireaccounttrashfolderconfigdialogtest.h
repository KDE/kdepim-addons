/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef EXPIREACCOUNTTRASHFOLDERCONFIGDIALOGTEST_H
#define EXPIREACCOUNTTRASHFOLDERCONFIGDIALOGTEST_H

#include <QObject>

class ExpireAccountTrashFolderConfigDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit ExpireAccountTrashFolderConfigDialogTest(QObject *parent = nullptr);
    ~ExpireAccountTrashFolderConfigDialogTest() = default;
};

#endif // EXPIREACCOUNTTRASHFOLDERCONFIGDIALOGTEST_H
