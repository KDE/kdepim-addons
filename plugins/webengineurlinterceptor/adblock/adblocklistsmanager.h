/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

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

    [[nodiscard]] QString filterListsPath() const;

private:
    const QString mFilterListsPath;
};
