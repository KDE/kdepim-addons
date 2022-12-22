/*
    SPDX-FileCopyrightText: 2004 Klarävdalens Datakonsult AB
    SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later WITH Qt-Commercial-exception-1.0
*/

#include "cryptopageplugin.h"

#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <qplugin.h>

#include <KContacts/Addressee>
#include <KIconLoader>
#include <KLocalizedString>
#include <QComboBox>
#include <QHBoxLayout>

#include <Libkleo/Enum>
#include <Libkleo/KeyRequester>

CryptoPagePlugin::CryptoPagePlugin()
    : mPgpKey(new Kleo::EncryptionKeyRequester(true, Kleo::EncryptionKeyRequester::OpenPGP, this))
    , mSmimeCert(new Kleo::EncryptionKeyRequester(true, Kleo::EncryptionKeyRequester::SMIME, this))
{
    KIconLoader::global()->addAppDir(QStringLiteral("libkleopatra"));

    auto topLayout = new QGridLayout(this);
    topLayout->setColumnStretch(1, 1);
    topLayout->setRowStretch(4, 1);

    auto protGB = new QGroupBox(i18n("Allowed Protocols"), this);
    auto protGBLayout = new QVBoxLayout;
    topLayout->addWidget(protGB, 0, 0, 1, 2);

    uint msgFormat = 1;
    for (uint i = 0; i < NumberOfProtocols; ++i) {
        auto f = static_cast<Kleo::CryptoMessageFormat>(msgFormat);
        mProtocolCB[i] = new QCheckBox(Kleo::cryptoMessageFormatToLabel(f), protGB);
        protGBLayout->addWidget(mProtocolCB[i]);

        // Iterating over a bitfield means *2 every time
        msgFormat *= 2;
    }
    protGB->setLayout(protGBLayout);

    auto l = new QLabel(i18n("Preferred OpenPGP encryption key:"), this);
    topLayout->addWidget(l, 1, 0);

    topLayout->addWidget(mPgpKey, 1, 1);

    l = new QLabel(i18n("Preferred S/MIME encryption certificate:"), this);
    topLayout->addWidget(l, 2, 0);

    topLayout->addWidget(mSmimeCert, 2, 1);

    auto box = new QGroupBox(i18n("Message Preference"), this);
    QLayout *boxLayout = new QVBoxLayout;
    topLayout->addWidget(box, 3, 0, 1, 2);

    // Send preferences/sign (see kleo/kleo/enum.h)
    auto hbox = new QWidget(box);
    auto hboxHBoxLayout = new QHBoxLayout(hbox);
    hboxHBoxLayout->setContentsMargins({});

    l = new QLabel(i18n("Sign:"), hbox);
    hboxHBoxLayout->addWidget(l);

    mSignPref = new QComboBox(hbox);
    hboxHBoxLayout->addWidget(mSignPref);
    l->setBuddy(mSignPref);
    mSignPref->setEditable(false);
    for (unsigned int i = Kleo::UnknownSigningPreference; i < Kleo::MaxSigningPreference; ++i) {
        mSignPref->addItem(Kleo::signingPreferenceToLabel(static_cast<Kleo::SigningPreference>(i)));
    }
    boxLayout->addWidget(hbox);

    // Send preferences/encrypt (see kleo/kleo/enum.h)
    hbox = new QWidget(box);
    hboxHBoxLayout = new QHBoxLayout(hbox);
    hboxHBoxLayout->setContentsMargins({});

    l = new QLabel(i18n("Encrypt:"), hbox);
    hboxHBoxLayout->addWidget(l);

    mCryptPref = new QComboBox(hbox);
    hboxHBoxLayout->addWidget(mCryptPref);
    l->setBuddy(mCryptPref);
    mCryptPref->setEditable(false);
    for (unsigned int i = Kleo::UnknownPreference; i < Kleo::MaxEncryptionPreference; ++i) {
        mCryptPref->addItem(Kleo::encryptionPreferenceToLabel(static_cast<Kleo::EncryptionPreference>(i)));
    }
    boxLayout->addWidget(hbox);
    box->setLayout(boxLayout);
}

CryptoPagePlugin::~CryptoPagePlugin() = default;

QString CryptoPagePlugin::title() const
{
    return i18n("Crypto Settings");
}

void CryptoPagePlugin::loadContact(const KContacts::Addressee &contact)
{
    const QStringList protocolPrefs =
        contact.custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("CRYPTOPROTOPREF")).split(QLatin1Char(','), Qt::SkipEmptyParts);
    const uint cryptoFormats = Kleo::stringListToCryptoMessageFormats(protocolPrefs);

    uint msgFormat = 1;
    for (uint i = 0; i < NumberOfProtocols; ++i, msgFormat *= 2) {
        mProtocolCB[i]->setChecked(cryptoFormats & msgFormat);
    }

    mSignPref->setCurrentIndex(Kleo::stringToSigningPreference(contact.custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("CRYPTOSIGNPREF"))));
    mCryptPref->setCurrentIndex(Kleo::stringToEncryptionPreference(contact.custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("CRYPTOENCRYPTPREF"))));

    // We don't use the contents of addr->key(...) because we want just a ref.
    // to the key/cert. stored elsewhere.

    mPgpKey->setFingerprints(contact.custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("OPENPGPFP")).split(QLatin1Char(','), Qt::SkipEmptyParts));
    mSmimeCert->setFingerprints(contact.custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("SMIMEFP")).split(QLatin1Char(','), Qt::SkipEmptyParts));
}

void CryptoPagePlugin::storeContact(KContacts::Addressee &contact) const
{
    uint cryptoFormats = 0;
    uint msgFormat = 1;
    for (uint i = 0; i < NumberOfProtocols; ++i, msgFormat *= 2) {
        if (mProtocolCB[i]->isChecked()) {
            cryptoFormats |= msgFormat;
        }
    }

    const QStringList protocolPref = Kleo::cryptoMessageFormatsToStringList(cryptoFormats);
    if (!protocolPref.isEmpty()) {
        contact.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("CRYPTOPROTOPREF"), protocolPref.join(QLatin1Char(',')));
    } else {
        contact.removeCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("CRYPTOPROTOPREF"));
    }

    const auto signPref = static_cast<Kleo::SigningPreference>(mSignPref->currentIndex());
    if (signPref != Kleo::UnknownSigningPreference) {
        contact.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("CRYPTOSIGNPREF"), QLatin1String(Kleo::signingPreferenceToString(signPref)));
    } else {
        contact.removeCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("CRYPTOSIGNPREF"));
    }

    const auto encryptPref = static_cast<Kleo::EncryptionPreference>(mCryptPref->currentIndex());
    if (encryptPref != Kleo::UnknownPreference) {
        contact.insertCustom(QStringLiteral("KADDRESSBOOK"),
                             QStringLiteral("CRYPTOENCRYPTPREF"),
                             QLatin1String(Kleo::encryptionPreferenceToString(encryptPref)));
    } else {
        contact.removeCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("CRYPTOENCRYPTPREF"));
    }

    const QStringList pfp = mPgpKey->fingerprints();
    const QStringList sfp = mSmimeCert->fingerprints();

    if (!pfp.isEmpty()) {
        contact.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("OPENPGPFP"), pfp.join(QLatin1Char(',')));
    } else {
        contact.removeCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("OPENPGPFP"));
    }

    if (!sfp.isEmpty()) {
        contact.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("SMIMEFP"), sfp.join(QLatin1Char(',')));
    } else {
        contact.removeCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("SMIMEFP"));
    }
}

void CryptoPagePlugin::setReadOnly(bool readOnly)
{
    mReadOnly = readOnly;
    for (uint i = 0; i < NumberOfProtocols; ++i) {
        mProtocolCB[i]->setEnabled(!readOnly);
    }

    mSignPref->setEnabled(!readOnly);
    mCryptPref->setEnabled(!readOnly);
    mPgpKey->setEnabled(!readOnly);
    mSmimeCert->setEnabled(!readOnly);
}
