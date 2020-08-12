/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ANTISPAMPLUGININTERFACE_H
#define ANTISPAMPLUGININTERFACE_H

#include <PimCommonAkonadi/GenericPluginInterface>

class AntiSpamPluginInterface : public PimCommon::GenericPluginInterface
{
public:
    explicit AntiSpamPluginInterface(QObject *parent = nullptr);
    ~AntiSpamPluginInterface() override;

    void exec() override;
    void createAction(KActionCollection *ac) override;

private:
    void slotActivated();
};

#endif // ANTISPAMPLUGININTERFACE_H
