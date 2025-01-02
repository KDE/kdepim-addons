/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommon/GenericPlugin>

#include <PimCommonAkonadi/GenericPluginInterface>

#include <QVariant>

class SearchDuplicatesPlugin : public PimCommon::GenericPlugin
{
    Q_OBJECT
public:
    explicit SearchDuplicatesPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~SearchDuplicatesPlugin() override;

    [[nodiscard]] PimCommon::GenericPluginInterface *createInterface(QObject *parent = nullptr) override;
};
