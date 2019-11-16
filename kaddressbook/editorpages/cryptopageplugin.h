/*
    Copyright (c) 2004 Klarälvdalens Datakonsult AB
                  2009 Tobias Koenig <tokoe@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

    As a special exception, permission is given to link this program
    with any edition of Qt, and distribute the resulting executable,
    without including the source code for Qt in the source distribution.
*/

#ifndef CRYPTOPAGEPLUGIN_H
#define CRYPTOPAGEPLUGIN_H

#include <ContactEditor/ContactEditorPagePlugin>

namespace Kleo {
class KeyRequester;
}

class QComboBox;
class QCheckBox;

class CryptoPagePlugin : public ContactEditor::ContactEditorPagePlugin
{
    Q_OBJECT
    Q_INTERFACES(ContactEditor::ContactEditorPagePlugin)
    Q_PLUGIN_METADATA(IID "org.kde.kaddressbook.CryptoPagePlugin")
public:
    CryptoPagePlugin();
    ~CryptoPagePlugin() override;
    Q_REQUIRED_RESULT QString title() const override;
    void loadContact(const KContacts::Addressee &contact) override;
    void storeContact(KContacts::Addressee &contact) const override;
    void setReadOnly(bool readOnly) override;

private:
    enum {
        NumberOfProtocols = 4
    };
    QCheckBox *mProtocolCB[NumberOfProtocols];
    QComboBox *mSignPref = nullptr;
    QComboBox *mCryptPref = nullptr;
    Kleo::KeyRequester *mPgpKey = nullptr;
    Kleo::KeyRequester *mSmimeCert = nullptr;
    bool mReadOnly = false;
};

#endif
