/*
   Copyright (C) 2015-2018 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef SENDVCARDSPLUGIN_H
#define SENDVCARDSPLUGIN_H

#include <pimcommon/genericplugin.h>

#include <PimCommonAkonadi/GenericPluginInterface>

#include <QVariant>

class SendVcardsPlugin : public PimCommon::GenericPlugin
{
    Q_OBJECT
public:
    explicit SendVcardsPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~SendVcardsPlugin() override;

    PimCommon::GenericPluginInterface *createInterface(KActionCollection *ac, QObject *parent = nullptr) override;
    bool hasPopupMenuSupport() const override;
};

#endif // SENDVCARDSPLUGIN_H
