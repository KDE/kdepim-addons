/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ANTIVIRUSPLUGININTERFACE_H
#define ANTIVIRUSPLUGININTERFACE_H

#include <PimCommonAkonadi/GenericPluginInterface>

class AntiVirusPluginInterface : public PimCommon::GenericPluginInterface
{
public:
    explicit AntiVirusPluginInterface(QObject *parent = nullptr);
    ~AntiVirusPluginInterface() override;

    void exec() override;
    void createAction(KActionCollection *ac) override;

private:
    void slotActivated();
};

#endif // ANTIVIRUSPLUGININTERFACE_H
