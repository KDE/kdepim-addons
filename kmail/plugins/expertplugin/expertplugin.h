/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef EXPERTPLUGIN_H
#define EXPERTPLUGIN_H

#include <PimCommon/GenericPlugin>

#include <PimCommonAkonadi/GenericPluginInterface>

#include <QVariant>

class ExpertPlugin : public PimCommon::GenericPlugin
{
    Q_OBJECT
public:
    explicit ExpertPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~ExpertPlugin() override;

    PimCommon::GenericPluginInterface *createInterface(QObject *parent = nullptr) override;
};

#endif // EXPERTPLUGIN_H
