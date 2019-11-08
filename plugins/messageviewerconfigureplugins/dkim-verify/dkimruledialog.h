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

#ifndef DKIMRULEDIALOG_H
#define DKIMRULEDIALOG_H

#include "dkimconfigure_private_export.h"
#include <QDialog>
#include <MessageViewer/DKIMRule>
class DKIMRuleWidget;
class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMRuleDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DKIMRuleDialog(QWidget *parent = nullptr);
    ~DKIMRuleDialog();

    MessageViewer::DKIMRule rule() const;
    void loadRule(const MessageViewer::DKIMRule &rule);
private:
    void slotAccepted();
    void writeConfig();
    void slotImport();
    void slotExport();
    void readConfig();
    DKIMRuleWidget *mRuleWidget = nullptr;
};

#endif // DKIMRULEDIALOG_H
