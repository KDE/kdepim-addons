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

#ifndef SELECTADDRESSTYPECOMBOBOX_H
#define SELECTADDRESSTYPECOMBOBOX_H

#include <KComboBox>
#include <KContacts/Address>

/**
 * @short A widget for selecting the type of an address.
 */
class SelectAddressTypeComboBox : public KComboBox
{
    Q_OBJECT

public:
    /**
     * Creates a new address type combo.
     *
     * @param parent The parent widget.
     */
    explicit SelectAddressTypeComboBox(QWidget *parent = nullptr);

    /**
     * Destroys the address type combo.
     */
    ~SelectAddressTypeComboBox();

    /**
     * Sets the type that shall be selected in the combobox.
     * @param type KABC address type to set.
     */
    void setType(KContacts::Address::Type type);

    /**
     * Returns the type that is currently selected.
     */
    KContacts::Address::Type type() const;

private Q_SLOTS:
    void selected(int);
    void otherSelected();

private:
    void update();

    KContacts::Address::Type mType;
    int mLastSelected;
    QList<int> mTypeList;
};
#endif
