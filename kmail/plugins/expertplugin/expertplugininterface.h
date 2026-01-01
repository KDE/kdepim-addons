/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommonAkonadi/GenericPluginInterface>

class ExpertPluginInterface : public PimCommon::GenericPluginInterface
{
    Q_OBJECT
public:
    explicit ExpertPluginInterface(QObject *parent = nullptr);
    ~ExpertPluginInterface() override;

    void exec() override;
    void createAction(KActionCollection *ac) override;

private:
    void slotActivated();
};
