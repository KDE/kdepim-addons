/*
   Copyright (C) 2014-2017 Montel Laurent <montel@kde.org>

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

#ifndef SEARCHDUPLICATERESULTWIDGETTEST_H
#define SEARCHDUPLICATERESULTWIDGETTEST_H

#include <QObject>

class SearchDuplicateResultWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit SearchDuplicateResultWidgetTest(QObject *parent = Q_NULLPTR);
    ~SearchDuplicateResultWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldHaveMergeButtonEnabled();
};

#endif // SEARCHDUPLICATERESULTWIDGETTEST_H
