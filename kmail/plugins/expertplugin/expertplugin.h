/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommon/GenericPlugin>

#include <PimCommonAkonadi/GenericPluginInterface>

#include <QVariant>

class ExpertPlugin : public PimCommon::GenericPlugin
{
    Q_OBJECT
public:
    explicit ExpertPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~ExpertPlugin() override;

    [[nodiscard]] PimCommon::GenericPluginInterface *createInterface(QObject *parent = nullptr) override;
};
