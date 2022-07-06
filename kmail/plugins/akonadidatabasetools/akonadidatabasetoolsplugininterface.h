/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommonAkonadi/GenericPluginInterface>

class AkonadiDatabaseToolsPluginInterface : public PimCommon::GenericPluginInterface
{
public:
    explicit AkonadiDatabaseToolsPluginInterface(QObject *parent = nullptr);
    ~AkonadiDatabaseToolsPluginInterface() override;

    void exec() override;
    void createAction(KActionCollection *ac) override;

private:
    void slotActivated();
};
