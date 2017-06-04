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

#ifndef ENTERPRISEHEADERSTYLEPLUGIN_H
#define ENTERPRISEHEADERSTYLEPLUGIN_H

#include "messageviewer/headerstyleplugin.h"

#include <QVariant>

namespace MessageViewer {
class EnterpriseHeaderStylePlugin : public MessageViewer::HeaderStylePlugin
{
    Q_OBJECT
public:
    explicit EnterpriseHeaderStylePlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~EnterpriseHeaderStylePlugin();

    HeaderStyle *headerStyle() const override;
    HeaderStrategy *headerStrategy() const override;
    HeaderStyleInterface *createView(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac, QObject *parent = nullptr) override;
    QString name() const override;
    bool hasMargin() const override;
    QString alignment() const override;
    int elidedTextSize() const override;
private:
    HeaderStyle *mHeaderStyle;
    HeaderStrategy *mHeaderStrategy;
};
}
#endif // ENTERPRISEHEADERSTYLEPLUGIN_H
