/*
   Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

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

#ifndef DKIMRULEWIDGET_H
#define DKIMRULEWIDGET_H
#include <QWidget>
#include "libdkimverifyconfigure_export.h"
#include <MessageViewer/DKIMRule>
class QCheckBox;
class QLineEdit;
class DKIMManageRulesComboBox;
class LIBDKIMVERIFYCONFIGURE_EXPORT DKIMRuleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DKIMRuleWidget(QWidget *parent = nullptr);
    ~DKIMRuleWidget();
    void loadRule(const MessageViewer::DKIMRule &rule);
    Q_REQUIRED_RESULT MessageViewer::DKIMRule rule() const;
private:
    QCheckBox *mEnabled = nullptr;
    QLineEdit *mDomain = nullptr;
    QLineEdit *mSignatureDomainIdentifier = nullptr;
    QLineEdit *mFrom = nullptr;
    QLineEdit *mListId = nullptr;
    DKIMManageRulesComboBox *mRuleType = nullptr;
};

#endif // DKIMRULEWIDGET_H
