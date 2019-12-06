/*
   Copyright (C) 2019 Laurent Montel <montel@kde.org>

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

#ifndef DKIMAUTHENTICATIONVERIFIEDSERVERWIDGET_H
#define DKIMAUTHENTICATIONVERIFIEDSERVERWIDGET_H

#include <QWidget>
#include "dkimconfigure_private_export.h"
#include <PimCommon/SimpleStringListEditor>

class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMAuthenticationVerifiedServerSelectorWidget : public PimCommon::SimpleStringListEditor
{
    Q_OBJECT
public:
    explicit DKIMAuthenticationVerifiedServerSelectorWidget(QWidget *parent = nullptr);
    ~DKIMAuthenticationVerifiedServerSelectorWidget();
};

class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMAuthenticationVerifiedServerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DKIMAuthenticationVerifiedServerWidget(QWidget *parent = nullptr);
    ~DKIMAuthenticationVerifiedServerWidget();
    void loadSettings();
    void saveSettings();
private:
    DKIMAuthenticationVerifiedServerSelectorWidget *mSelector = nullptr;
};

#endif // DKIMAUTHENTICATIONVERIFIEDSERVERWIDGET_H
