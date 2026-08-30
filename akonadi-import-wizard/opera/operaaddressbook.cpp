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
        if (line == QLatin1StringView("#CONTACT")) {
            appendContact(contact);
            foundContact = true;
        } else if (line == QLatin1StringView("#FOLDER")) {
            appendContact(contact);
            foundContact = false;
            // TODO
        } else if (foundContact) {
            line = line.trimmed();
            if (!contact) {
                contact = new KContacts::Addressee;
            }
            if (line.startsWith(QLatin1StringView("ID"))) {
                // Nothing
            } else if (line.startsWith(QLatin1StringView("NAME"))) {
                contact->setName(line.remove(u"NAME="_s));
            } else if (line.startsWith(QLatin1StringView("URL"))) {
                KContacts::ResourceLocatorUrl url;
                url.setUrl(QUrl(line.remove(u"URL="_s)));
                contact->setUrl(url);
            } else if (line.startsWith(QLatin1StringView("DESCRIPTION"))) {
                contact->setNote(line.remove(u"DESCRIPTION="_s));
            } else if (line.startsWith(QLatin1StringView("PHONE"))) {
                contact->insertPhoneNumber(KContacts::PhoneNumber(line.remove(u"PHONE="_s), KContacts::PhoneNumber::Home));
            } else if (line.startsWith(QLatin1StringView("FAX"))) {
                contact->insertPhoneNumber(KContacts::PhoneNumber(line.remove(u"FAX="_s), KContacts::PhoneNumber::Fax));
            } else if (line.startsWith(QLatin1StringView("POSTALADDRESS"))) {
                // TODO
            } else if (line.startsWith(QLatin1StringView("PICTUREURL"))) {
                // TODO
            } else if (line.startsWith(QLatin1StringView("ICON"))) {
                // TODO
            } else if (line.startsWith(QLatin1StringView("SHORT NAME"))) {
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
