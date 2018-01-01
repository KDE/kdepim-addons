/*
   Copyright (C) 2016-2018 Montel Laurent <montel@kde.org>

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

#ifndef AUTOMATICADDCONTACTSTabWIDGETTEST_H
#define AUTOMATICADDCONTACTSTabWIDGETTEST_H

#include <QObject>
class QStandardItemModel;
class AutomaticAddContactsTabWidget;
class AutomaticAddContactsTabWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit AutomaticAddContactsTabWidgetTest(QObject *parent = nullptr);
    ~AutomaticAddContactsTabWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldResetValue();
private:
    AutomaticAddContactsTabWidget *createContactWidget();
    QStandardItemModel *mComboboxModel = nullptr;
};

#endif // AUTOMATICADDCONTACTSTabWIDGETTEST_H
