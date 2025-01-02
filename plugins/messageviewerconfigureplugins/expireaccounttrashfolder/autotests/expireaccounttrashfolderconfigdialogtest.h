/*
   SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ExpireAccountTrashFolderConfigDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit ExpireAccountTrashFolderConfigDialogTest(QObject *parent = nullptr);
    ~ExpireAccountTrashFolderConfigDialogTest() override = default;
};
