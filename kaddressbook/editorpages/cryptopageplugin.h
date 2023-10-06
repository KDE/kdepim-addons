/*
    SPDX-FileCopyrightText: 2004 Klarävdalens Datakonsult AB
    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later WITH Qt-Commercial-exception-1.0
*/

#pragma once

#include <Akonadi/ContactEditorPagePlugin>

namespace Kleo
{
class KeyRequester;
}

class QComboBox;
class QCheckBox;

class CryptoPagePlugin : public Akonadi::ContactEditorPagePlugin
{
    Q_OBJECT
    Q_INTERFACES(Akonadi::ContactEditorPagePlugin)
    Q_PLUGIN_METADATA(IID "org.kde.kaddressbook.CryptoPagePlugin")
public:
    CryptoPagePlugin();
    ~CryptoPagePlugin() override;
    [[nodiscard]] QString title() const override;
    void loadContact(const KContacts::Addressee &contact) override;
    void storeContact(KContacts::Addressee &contact) const override;
    void setReadOnly(bool readOnly) override;

private:
    enum { NumberOfProtocols = 4 };
    QCheckBox *mProtocolCB[NumberOfProtocols];
    QComboBox *mSignPref = nullptr;
    QComboBox *mCryptPref = nullptr;
    Kleo::KeyRequester *const mPgpKey;
    Kleo::KeyRequester *const mSmimeCert;
    bool mReadOnly = false;
};
