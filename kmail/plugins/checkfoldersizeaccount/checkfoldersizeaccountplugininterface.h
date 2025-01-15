/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommonAkonadi/GenericPluginInterface>

class CheckFolderSizeAccountPluginInterface : public PimCommon::GenericPluginInterface
{
public:
    explicit CheckFolderSizeAccountPluginInterface(QObject *parent = nullptr);
    ~CheckFolderSizeAccountPluginInterface() override;

    void exec() override;
    void createAction(KActionCollection *ac) override;
};
