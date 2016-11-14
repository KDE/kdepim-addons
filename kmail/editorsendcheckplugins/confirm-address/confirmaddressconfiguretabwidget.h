/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#ifndef CONFIRMADDRESSCONFIGURETABWIDGET_H
#define CONFIRMADDRESSCONFIGURETABWIDGET_H

#include <QWidget>
namespace PimCommon
{
class SimpleStringListEditor;
}
class KConfigGroup;
class QRadioButton;
class ConfirmAddressConfigureTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfirmAddressConfigureTabWidget(QWidget *parent = Q_NULLPTR);
    ~ConfirmAddressConfigureTabWidget();

    void resetSettings();
    void loadSettings(const KConfigGroup &grp);
    void saveSettings(KConfigGroup &grp);

    void setIdentity(uint identity);

Q_SIGNALS:
    void configureChanged();

private:
    uint mIdentity;
    PimCommon::SimpleStringListEditor *mDomainNameListEditor;
    PimCommon::SimpleStringListEditor *mWhiteListEditor;
    QRadioButton *mAcceptedDomain;
    QRadioButton *mRejectedDomain;
};

#endif // CONFIRMADDRESSCONFIGURETABWIDGET_H
