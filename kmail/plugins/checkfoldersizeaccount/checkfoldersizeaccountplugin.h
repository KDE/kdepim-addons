/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <PimCommon/GenericPlugin>

#include <PimCommonAkonadi/GenericPluginInterface>

#include <QVariant>

class CheckFolderSizeAccountPlugin : public PimCommon::GenericPlugin
{
    Q_OBJECT
public:
    explicit CheckFolderSizeAccountPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~CheckFolderSizeAccountPlugin() override;

    [[nodiscard]] PimCommon::GenericPluginInterface *createInterface(QObject *parent = nullptr) override;
    [[nodiscard]] bool hasConfigureDialog() const override;
    void showConfigureDialog(QWidget *parent = nullptr) override;
};
