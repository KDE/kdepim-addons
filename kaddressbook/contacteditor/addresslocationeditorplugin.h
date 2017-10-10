/*
   Copyright (C) 2017 Montel Laurent <montel@kde.org>

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

#ifndef ADDRESSLOCATIONEDITORPLUGIN_H
#define ADDRESSLOCATIONEDITORPLUGIN_H

#include <QWidget>
#include <ContactEditor/AbstractAddressLocationWidget>
class QLineEdit;
class QToolButton;
class AddressLocationEditor : public ContactEditor::AbstractAddressLocationWidget
{
    Q_OBJECT
public:
    explicit AddressLocationEditor(QWidget *parent = nullptr, const QList<QVariant> & =
    {
    });
    ~AddressLocationEditor();

    void loadContact(const KContacts::Addressee &contact) override;
    void storeContact(KContacts::Addressee &contact) const override;
    void setReadOnly(bool readOnly) override;
};

#endif // ADDRESSLOCATIONEDITORPLUGIN_H
