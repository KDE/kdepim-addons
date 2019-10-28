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
#ifndef DKIMMANAGERULESDIALOG_H
#define DKIMMANAGERULESDIALOG_H

#include <QDialog>
#include "dkimconfigure_private_export.h"
class DKIMManageRulesWidget;
class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMManageRulesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DKIMManageRulesDialog(QWidget *parent = nullptr);
    ~DKIMManageRulesDialog();

private:
    void slotAccepted();
    void readConfig();
    void writeConfig();
    DKIMManageRulesWidget *mRulesWidget = nullptr;
};

#endif // DKIMMANAGERULESDIALOG_H
