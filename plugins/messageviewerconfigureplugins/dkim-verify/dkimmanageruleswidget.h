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

#ifndef DKIMMANAGERULESWIDGET_H
#define DKIMMANAGERULESWIDGET_H
#include "dkimconfigure_private_export.h"
#include <MessageViewer/DKIMRule>
#include <QTreeWidgetItem>
#include <QWidget>
class QTreeWidget;

class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMManageRulesWidgetItem : public QTreeWidgetItem
{
public:
    explicit DKIMManageRulesWidgetItem(QTreeWidget *parent = nullptr);
    ~DKIMManageRulesWidgetItem();

    Q_REQUIRED_RESULT MessageViewer::DKIMRule rule() const;
    void setRule(const MessageViewer::DKIMRule &rule);

private:
    MessageViewer::DKIMRule mRule;
};

class LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT DKIMManageRulesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DKIMManageRulesWidget(QWidget *parent = nullptr);
    ~DKIMManageRulesWidget();
    void loadSettings();
    void saveSettings();
private:
    void customContextMenuRequested(const QPoint &);
    QTreeWidget *mTreeWidget = nullptr;
};

#endif // DKIMMANAGERULESWIDGET_H
