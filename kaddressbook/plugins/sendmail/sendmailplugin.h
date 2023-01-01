/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommon/GenericPlugin>

#include <PimCommonAkonadi/GenericPluginInterface>

#include <QVariant>

class SendMailPlugin : public PimCommon::GenericPlugin
{
    Q_OBJECT
public:
    explicit SendMailPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~SendMailPlugin() override;

    PimCommon::GenericPluginInterface *createInterface(QObject *parent = nullptr) override;
    Q_REQUIRED_RESULT bool hasPopupMenuSupport() const override;
};
