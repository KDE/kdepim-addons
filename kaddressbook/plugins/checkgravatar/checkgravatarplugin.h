/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CHECKGRAVATARPLUGIN_H
#define CHECKGRAVATARPLUGIN_H

#include <PimCommon/GenericPlugin>

#include <PimCommonAkonadi/GenericPluginInterface>

#include <QVariant>

class CheckGravatarPlugin : public PimCommon::GenericPlugin
{
    Q_OBJECT
public:
    explicit CheckGravatarPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~CheckGravatarPlugin() override;

    PimCommon::GenericPluginInterface *createInterface(QObject *parent = nullptr) override;

    Q_REQUIRED_RESULT bool hasPopupMenuSupport() const override;
};

#endif // CHECKGRAVATARPLUGIN_H
