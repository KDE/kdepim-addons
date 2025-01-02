/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommon/GenericPlugin>

#include <PimCommonAkonadi/GenericPluginInterface>

#include <QVariant>

class AntiVirusPlugin : public PimCommon::GenericPlugin
{
    Q_OBJECT
public:
    explicit AntiVirusPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~AntiVirusPlugin() override;

    [[nodiscard]] PimCommon::GenericPluginInterface *createInterface(QObject *parent = nullptr) override;
};
