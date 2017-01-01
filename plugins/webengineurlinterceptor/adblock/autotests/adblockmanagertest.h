/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

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

#ifndef ADBLOCKMANAGERTEST_H
#define ADBLOCKMANAGERTEST_H

#include <QObject>

class AdblockManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit AdblockManagerTest(QObject *parent = Q_NULLPTR);
    ~AdblockManagerTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // ADBLOCKMANAGERTEST_H
