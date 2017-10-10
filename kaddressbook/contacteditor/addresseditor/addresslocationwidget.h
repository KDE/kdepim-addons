/*
    This file is part of Contact Editor.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016-2017 Laurent Montel <laurent.montel@kdab.com>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#ifndef ADDRESSLOCATIONWIDGET_H
#define ADDRESSLOCATIONWIDGET_H

#include <QWidget>
#include <KContacts/Address>
class QStackedWidget;
class QCheckBox;
class KLineEdit;
class KComboBox;
class QPushButton;
class SelectAddressTypeComboBox;
class AddressLocationWidget : public QWidget
{
    Q_OBJECT
public:
    enum Mode {
        CreateAddress = 0,
        ModifyAddress
    };

    explicit AddressLocationWidget(QWidget *parent = nullptr);
    ~AddressLocationWidget();

    void setAddress(const KContacts::Address &address);
    KContacts::Address address() const;

    void slotModifyAddress(const KContacts::Address &address, int currentIndex);

    void clear();

    void setReadOnly(bool readOnly);

Q_SIGNALS:
    void addNewAddress(const KContacts::Address &address);
    void updateAddress(const KContacts::Address &address, int index);
    void updateAddressCanceled();

private:
    void slotAddAddress();
    void slotUpdateAddress();
    void slotCancelModifyAddress();
    void fillCountryCombo();
    void switchMode();
    void reset();
    KContacts::Address mAddress;
    QCheckBox *mPreferredCheckBox = nullptr;
    KLineEdit *mPOBoxEdit = nullptr;
    KLineEdit *mLocalityEdit = nullptr;
    KLineEdit *mRegionEdit = nullptr;
    KLineEdit *mPostalCodeEdit = nullptr;
    KLineEdit *mStreetEdit = nullptr;
    KComboBox *mCountryCombo = nullptr;
    QPushButton *mAddAddress = nullptr;
    QPushButton *mModifyAddress = nullptr;
    QPushButton *mCancelAddress = nullptr;
    QStackedWidget *mButtonStack = nullptr;
    SelectAddressTypeComboBox *mTypeCombo = nullptr;
    int mCurrentAddress;
    Mode mCurrentMode;
};
#endif // ADDRESSLOCATIONWIDGET_H
