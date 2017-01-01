/*
   Copyright (C) 2015-2017 Montel Laurent <montel@kde.org>

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

#ifndef ALLHEADERSTYLEPLUGIN_H
#define ALLHEADERSTYLEPLUGIN_H

#include "messageviewer/headerstyleplugin.h"

#include <QVariant>

namespace MessageViewer
{
class AllHeaderStylePlugin : public MessageViewer::HeaderStylePlugin
{
    Q_OBJECT
public:
    explicit AllHeaderStylePlugin(QObject *parent = Q_NULLPTR, const QList<QVariant> & = QList<QVariant>());
    ~AllHeaderStylePlugin();

    HeaderStyle *headerStyle() const Q_DECL_OVERRIDE;
    HeaderStrategy *headerStrategy() const Q_DECL_OVERRIDE;
    HeaderStyleInterface *createView(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac, QObject *parent = Q_NULLPTR) Q_DECL_OVERRIDE;
    QString name() const Q_DECL_OVERRIDE;
private:
    HeaderStyle *mHeaderStyle;
    HeaderStrategy *mHeaderStrategy;
};
}
#endif // ALLHEADERSTYLEPLUGIN_H
