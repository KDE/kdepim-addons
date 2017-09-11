/*
   Copyright (c) 2015-2017 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef STANDARDSHEADERSTYLEPLUGIN_H
#define STANDARDSHEADERSTYLEPLUGIN_H

#include "messageviewer/headerstyleplugin.h"

#include <QVariant>

namespace MessageViewer {
class StandardsHeaderStylePlugin : public MessageViewer::HeaderStylePlugin
{
    Q_OBJECT
public:
    explicit StandardsHeaderStylePlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~StandardsHeaderStylePlugin();

    HeaderStyle *headerStyle() const override;
    HeaderStrategy *headerStrategy() const override;
    HeaderStyleInterface *createView(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac, QObject *parent = nullptr) override;
    QString name() const override;
private:
    HeaderStyle *mHeaderStyle = nullptr;
    HeaderStrategy *mHeaderStrategy = nullptr;
};
}
#endif // STANDARDSHEADERSTYLEPLUGIN_H
