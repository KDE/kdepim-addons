/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef EXPERTPLUGININTERFACE_H
#define EXPERTPLUGININTERFACE_H

#include <PimCommonAkonadi/GenericPluginInterface>

class ExpertPluginInterface : public PimCommon::GenericPluginInterface
{
public:
    explicit ExpertPluginInterface(QObject *parent = nullptr);
    ~ExpertPluginInterface() override;

    void exec() override;
    void createAction(KActionCollection *ac) override;

private:
    void slotActivated();
};

#endif // EXPERTPLUGININTERFACE_H
