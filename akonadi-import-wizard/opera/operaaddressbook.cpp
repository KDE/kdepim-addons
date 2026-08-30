/*
   SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "operaaddressbook.h"

#include "operaplugin_debug.h"
#include <KContacts/Addressee>
#include <QFile>
#include <QUrl>
using namespace Qt::Literals::StringLiterals;

OperaAddressBook::OperaAddressBook(const QString &filename)
    : mFileName(filename)
{
}

void OperaAddressBook::importAddressBook()
{
    QFile file(mFileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qCDebug(OPERAPLUGIN_LOG) << " We can't open file" << mFileName;
        return;
    }

    QTextStream stream(&file);
    bool foundContact = false;
    KContacts::Addressee *contact = nullptr;
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        if (line == "#CONTACT"_L1) {
            appendContact(contact);
            foundContact = true;
        } else if (line == "#FOLDER"_L1) {
            appendContact(contact);
            foundContact = false;
            // TODO
        } else if (foundContact) {
            line = line.trimmed();
            if (!contact) {
                contact = new KContacts::Addressee;
            }
            if (line.startsWith("ID"_L1)) {
                // Nothing
            } else if (line.startsWith("NAME"_L1)) {
                contact->setName(line.remove(u"NAME="_s));
            } else if (line.startsWith("URL"_L1)) {
                KContacts::ResourceLocatorUrl url;
                url.setUrl(QUrl(line.remove(u"URL="_s)));
                contact->setUrl(url);
            } else if (line.startsWith("DESCRIPTION"_L1)) {
                contact->setNote(line.remove(u"DESCRIPTION="_s));
            } else if (line.startsWith("PHONE"_L1)) {
                contact->insertPhoneNumber(KContacts::PhoneNumber(line.remove(u"PHONE="_s), KContacts::PhoneNumber::Home));
            } else if (line.startsWith("FAX"_L1)) {
                contact->insertPhoneNumber(KContacts::PhoneNumber(line.remove(u"FAX="_s), KContacts::PhoneNumber::Fax));
            } else if (line.startsWith("POSTALADDRESS"_L1)) {
                // TODO
            } else if (line.startsWith("PICTUREURL"_L1)) {
                // TODO
            } else if (line.startsWith("ICON"_L1)) {
                // TODO
            } else if (line.startsWith("SHORT NAME"_L1)) {
                contact->setNickName(line.remove(u"SHORT NAME="_s));
            }
        }
    }
    appendContact(contact);
}

OperaAddressBook::~OperaAddressBook() = default;

void OperaAddressBook::appendContact(KContacts::Addressee *contact)
{
    if (contact) {
        addImportContactNote(*contact, u"Opera"_s);
        createContact(*contact);
        delete contact;
    }
}
