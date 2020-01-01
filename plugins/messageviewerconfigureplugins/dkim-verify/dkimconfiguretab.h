/*
   Copyright (C) 2018-2020 Laurent Montel <montel@kde.org>

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

#ifndef DKIMCONFIGURETAB_H
#define DKIMCONFIGURETAB_H

#include <QWidget>
#include "dkimconfigure_private_export.h"

class QTabWidget;
class DKIMGeneralWidget;
class DKIMKeyRecordWidget;
class DKIMAdvancedWidget;
class DKIMPolicyWidget;
class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMConfigureTab : public QWidget
{
    Q_OBJECT
public:
    explicit DKIMConfigureTab(QWidget *parent = nullptr);
    ~DKIMConfigureTab();

    void loadSettings();
    void saveSettings();
    void resetSettings();

private:
    void initTab();
    DKIMGeneralWidget *mGeneralWidget = nullptr;
    DKIMKeyRecordWidget *mRecordWidget = nullptr;
    DKIMAdvancedWidget *mAdvancedWidget = nullptr;
    DKIMPolicyWidget *mPolicyWidget = nullptr;
    QTabWidget *mTabWidget = nullptr;
};

#endif // DKIMCONFIGURETAB_H
