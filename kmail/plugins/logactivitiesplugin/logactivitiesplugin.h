/*
   Copyright (C) 2017-2020 Laurent Montel <montel@kde.org>

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

#ifndef LOGACTIVITIESPLUGIN_H
#define LOGACTIVITIESPLUGIN_H

#include <pimcommon/genericplugin.h>

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
