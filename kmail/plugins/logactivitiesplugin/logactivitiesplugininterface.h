/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LOGACTIVITIESPLUGININTERFACE_H
#define LOGACTIVITIESPLUGININTERFACE_H

#include <PimCommonAkonadi/GenericPluginInterface>

class LogActivitiesPluginInterface : public PimCommon::GenericPluginInterface
{
public:
    explicit LogActivitiesPluginInterface(QObject *parent = nullptr);
    ~LogActivitiesPluginInterface() override;

    void exec() override;
    void createAction(KActionCollection *ac) override;

private:
    void slotActivated();
};

#endif // LOGACTIVITIESPLUGININTERFACE_H
