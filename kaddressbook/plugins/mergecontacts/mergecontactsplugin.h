/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MERGECONTACTSPLUGIN_H
#define MERGECONTACTSPLUGIN_H

#include <PimCommon/GenericPlugin>

#include <PimCommonAkonadi/GenericPluginInterface>

#include <QVariant>

class MergeContactsPlugin : public PimCommon::GenericPlugin
{
    Q_OBJECT
public:
    explicit MergeContactsPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~MergeContactsPlugin() override;

    PimCommon::GenericPluginInterface *createInterface(QObject *parent = nullptr) override;
};

#endif // MERGECONTACTSPLUGIN_H
