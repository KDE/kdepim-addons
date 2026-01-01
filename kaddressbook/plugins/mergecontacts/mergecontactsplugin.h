/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommon/GenericPlugin>

#include <PimCommonAkonadi/GenericPluginInterface>

#include <QVariant>

class MergeContactsPlugin : public PimCommon::GenericPlugin
{
    Q_OBJECT
public:
    explicit MergeContactsPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~MergeContactsPlugin() override;

    [[nodiscard]] PimCommon::GenericPluginInterface *createInterface(QObject *parent = nullptr) override;
};
