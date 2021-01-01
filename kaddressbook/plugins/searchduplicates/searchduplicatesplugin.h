/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SEARCHDUPLICATESPLUGIN_H
#define SEARCHDUPLICATESPLUGIN_H

#include <PimCommon/GenericPlugin>

#include <PimCommonAkonadi/GenericPluginInterface>

#include <QVariant>

class SearchDuplicatesPlugin : public PimCommon::GenericPlugin
{
    Q_OBJECT
public:
    explicit SearchDuplicatesPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~SearchDuplicatesPlugin() override;

    PimCommon::GenericPluginInterface *createInterface(QObject *parent = nullptr) override;
};

#endif // SEARCHDUPLICATESPLUGIN_H
