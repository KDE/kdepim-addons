/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class AdblockManager : public QObject
{
    Q_OBJECT
public:
    explicit AdblockManager(QObject *parent = nullptr);
    ~AdblockManager() override;

    static AdblockManager *self();
};
