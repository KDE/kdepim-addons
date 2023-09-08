/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class AdblockListsManager : public QObject
{
    Q_OBJECT
public:
    explicit AdblockListsManager(QObject *parent = nullptr);
    ~AdblockListsManager() override;

    Q_REQUIRED_RESULT QString filterListsPath() const;

private:
    const QString mFilterListsPath;
};
