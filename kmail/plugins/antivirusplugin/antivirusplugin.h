/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ANTIVIRUSPLUGIN_H
#define ANTIVIRUSPLUGIN_H

#include <PimCommon/GenericPlugin>

#include <PimCommonAkonadi/GenericPluginInterface>

#include <QVariant>

class AntiVirusPlugin : public PimCommon::GenericPlugin
{
    Q_OBJECT
public:
    explicit AntiVirusPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~AntiVirusPlugin() override;

    PimCommon::GenericPluginInterface *createInterface(QObject *parent = nullptr) override;
};

#endif // ANTIVIRUSPLUGIN_H
