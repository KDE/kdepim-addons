/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommon/GenericPlugin>

#include <PimCommonAkonadi/GenericPluginInterface>

#include <QVariant>

class LogActivitiesPlugin : public PimCommon::GenericPlugin
{
    Q_OBJECT
public:
    explicit LogActivitiesPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~LogActivitiesPlugin() override;

    PimCommon::GenericPluginInterface *createInterface(QObject *parent = nullptr) override;
};

