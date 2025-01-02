/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "akonadidatabasetoolsutils.h"
#include "akonadidatasetools_export.h"
#include <PimCommonAkonadi/GenericPluginInterface>
class AKONADIDATASETOOLS_EXPORT AkonadiDatabaseToolsPluginInterface : public PimCommon::GenericPluginInterface
{
public:
    explicit AkonadiDatabaseToolsPluginInterface(QObject *parent = nullptr);
    ~AkonadiDatabaseToolsPluginInterface() override;

    void exec() override;
    void createAction(KActionCollection *ac) override;

private:
    AKONADIDATASETOOLS_NO_EXPORT void slotActivated();
    AkonadiDatabaseToolsUtils::AkonadiDatabaseTool mTool = AkonadiDatabaseToolsUtils::AkonadiDatabaseTool::Unknown;
};
