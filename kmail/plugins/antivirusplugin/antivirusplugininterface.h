/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommonAkonadi/GenericPluginInterface>

class AntiVirusPluginInterface : public PimCommon::GenericPluginInterface
{
    Q_OBJECT
public:
    explicit AntiVirusPluginInterface(QObject *parent = nullptr);
    ~AntiVirusPluginInterface() override;

    void exec() override;
    void createAction(KActionCollection *ac) override;

private:
    void slotActivated();
};
