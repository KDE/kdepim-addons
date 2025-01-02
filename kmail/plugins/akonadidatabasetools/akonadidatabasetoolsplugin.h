/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommon/GenericPlugin>

#include <PimCommonAkonadi/GenericPluginInterface>

#include <QVariant>

class AkonadiDatabaseToolsPlugin : public PimCommon::GenericPlugin
{
    Q_OBJECT
public:
    explicit AkonadiDatabaseToolsPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~AkonadiDatabaseToolsPlugin() override;

    [[nodiscard]] PimCommon::GenericPluginInterface *createInterface(QObject *parent = nullptr) override;
};
