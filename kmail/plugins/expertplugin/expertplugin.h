/*
   SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

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

    PimCommon::GenericPluginInterface *createInterface(QObject *parent = nullptr) override;
};
