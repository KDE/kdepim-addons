/*
   Copyright (C) 2015-2016 Montel Laurent <montel@kde.org>

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

#ifndef TRIOPABSHORTURLENGINEINTERFACE_H
#define TRIOPABSHORTURLENGINEINTERFACE_H

#include "../../shorturlengineplugin/shorturlengineinterface.h"

class QNetworkReply;
class TripAbShortUrlEngineInterface : public ShortUrlEngineInterface
{
    Q_OBJECT
public:
    explicit TripAbShortUrlEngineInterface(ShortUrlEnginePlugin *plugin, QObject *parent = Q_NULLPTR);
    ~TripAbShortUrlEngineInterface();

    void generateShortUrl() Q_DECL_OVERRIDE;
    QString engineName() const Q_DECL_OVERRIDE;

private Q_SLOTS:
    void slotShortUrlFinished(QNetworkReply *reply);
};

#endif
