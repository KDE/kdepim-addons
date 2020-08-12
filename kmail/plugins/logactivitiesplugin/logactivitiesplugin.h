/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LOGACTIVITIESPLUGIN_H
#define LOGACTIVITIESPLUGIN_H

#include <PimCommon/GenericPlugin>

#include <PimCommonAkonadi/GenericPluginInterface>

#include <QVariant>

class LogActivitiesPlugin : public PimCommon::GenericPlugin
{
    Q_OBJECT
public:
    explicit LogActivitiesPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~LogActivitiesPlugin() override;

    PimCommon::GenericPluginInterface *createInterface(QObject *parent = nullptr) override;
};

#endif // LOGACTIVITIESPLUGIN_H
