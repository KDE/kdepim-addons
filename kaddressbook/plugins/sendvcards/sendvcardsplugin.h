/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SENDVCARDSPLUGIN_H
#define SENDVCARDSPLUGIN_H

#include <PimCommon/GenericPlugin>

#include <PimCommonAkonadi/GenericPluginInterface>

#include <QVariant>

class SendVcardsPlugin : public PimCommon::GenericPlugin
{
    Q_OBJECT
public:
    explicit SendVcardsPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~SendVcardsPlugin() override;

    Q_REQUIRED_RESULT PimCommon::GenericPluginInterface *createInterface(QObject *parent = nullptr) override;
    Q_REQUIRED_RESULT bool hasPopupMenuSupport() const override;
};

#endif // SENDVCARDSPLUGIN_H
