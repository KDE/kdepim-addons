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

#include "vcardimportexportplugininterface.h"
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>
#include <KAddressBookImportExport/KAddressBookContactSelectionDialog>
#include <QPointer>
#include <KMessageBox>
#include <QUrl>
#include <KContacts/VCardConverter>

#ifdef QGPGME_FOUND
#include <gpgme++/context.h>
#include <gpgme++/data.h>
#include <gpgme++/key.h>
#include <qgpgme/dataprovider.h>
#endif // QGPGME_FOUND

VCardImportExportPluginInterface::VCardImportExportPluginInterface(QObject *parent)
    : KAddressBookImportExport::KAddressBookImportExportPluginInterface(parent),
      mExportVCardType(VCard3)
{

}

VCardImportExportPluginInterface::~VCardImportExportPluginInterface()
{

}


void VCardImportExportPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = ac->addAction(QStringLiteral("file_import_vcard"));
    action->setText(i18n("Import vCard..."));
    action->setWhatsThis(i18n("Import contacts from a vCard file."));
    connect(action, &QAction::triggered, this, &VCardImportExportPluginInterface::slotImportVCard);
    setImportActions(QList<QAction *>() << action);

    QList<QAction *> exportActionList;

    action = ac->addAction(QStringLiteral("file_export_vcard40"));
    action->setWhatsThis(i18n("Export contacts to a vCard 4.0 file."));
    action->setText(i18n("Export vCard 4.0..."));
    connect(action, &QAction::triggered, this, &VCardImportExportPluginInterface::slotExportVCard4);
    exportActionList << action;

    action = ac->addAction(QStringLiteral("file_export_vcard30"));
    action->setText(i18n("Export vCard 3.0..."));
    action->setWhatsThis(i18n("Export contacts to a vCard 3.0 file."));
    connect(action, &QAction::triggered, this, &VCardImportExportPluginInterface::slotExportVCard3);
    exportActionList << action;

    action = ac->addAction(QStringLiteral("file_export_vcard21"));
    action->setText(i18n("Export vCard 2.1..."));
    action->setWhatsThis(i18n("Export contacts to a vCard 2.1 file."));
    connect(action, &QAction::triggered, this, &VCardImportExportPluginInterface::slotExportVCard2);
    exportActionList << action;
    setExportActions(exportActionList);
}

void VCardImportExportPluginInterface::slotExportVCard4()
{
    mImportExportAction = Export;
    mExportVCardType = VCard4;
    Q_EMIT emitPluginActivated(this);
}

void VCardImportExportPluginInterface::slotExportVCard3()
{
    mImportExportAction = Export;
    mExportVCardType = VCard3;
    Q_EMIT emitPluginActivated(this);
}

void VCardImportExportPluginInterface::slotExportVCard2()
{
    mImportExportAction = Export;
    mExportVCardType = VCard2_1;
    Q_EMIT emitPluginActivated(this);
}

void VCardImportExportPluginInterface::exec()
{
    switch(mImportExportAction) {
    case Import:
        importVCard();
        break;
    case Export:
        exportVCard();
        break;
    }
}

void VCardImportExportPluginInterface::slotImportVCard()
{
    mImportExportAction = Import;
    Q_EMIT emitPluginActivated(this);
}

void VCardImportExportPluginInterface::importVCard()
{
#if 0
    KAddressBookImportExport::KAddressBookImportExportContactList contactList;
    KContacts::Addressee::List addrList;
    QList<QUrl> urls;

    if (!option(QStringLiteral("importData")).isEmpty()) {
        addrList = parseVCard(option(QStringLiteral("importData")).toUtf8());
    } else {
        if (!option(QStringLiteral("importUrl")).isEmpty()) {
            urls.append(QUrl::fromLocalFile(option(QStringLiteral("importUrl"))));
        } else {
            const QString filter = i18n("*.vcf|vCard (*.vcf)\n*|all files (*)");
            urls =
                QFileDialog::getOpenFileUrls(parentWidget(), i18nc("@title:window", "Select vCard to Import"),
                                             QUrl(),
                                             filter);
        }

        if (urls.isEmpty()) {
            return contactList;
        }

        const QString caption(i18nc("@title:window", "vCard Import Failed"));
        bool anyFailures = false;

        const int numberOfUrl(urls.count());
        for (int i = 0; i < numberOfUrl; ++i) {
            const QUrl url = urls.at(i);

            auto job = KIO::storedGet(url);
            KJobWidgets::setWindow(job, parentWidget());
            if (job->exec()) {

                const QByteArray data = job->data();
                if (!data.isEmpty()) {
                    addrList += parseVCard(data);
                }
            } else {
                const QString msg = xi18nc(
                                        "@info",
                                        "<para>Unable to access vCard:</para><para>%1</para>",
                                        job->errorString());
                KMessageBox::error(parentWidget(), msg, caption);
                anyFailures = true;
            }
        }

        if (!option(QStringLiteral("importUrl")).isEmpty()) {     // a vcard was passed via cmd
            if (addrList.isEmpty()) {
                if (anyFailures && urls.count() > 1) {
                    KMessageBox::information(
                        parentWidget(),
                        i18nc("@info", "No contacts were imported, due to errors with the vCards."));
                } else if (!anyFailures) {
                    KMessageBox::information(
                        parentWidget(),
                        i18nc("@info", "The vCard does not contain any contacts."));
                }
            } else {
                QPointer<VCardViewerDialog> dlg = new VCardViewerDialog(addrList, parentWidget());
                if (dlg->exec() && dlg) {
                    addrList = dlg->contacts();
                } else {
                    addrList.clear();
                }
                delete dlg;
            }
        }
    }
    contactList.setAddressList(addrList);
#endif
}

KContacts::Addressee::List VCardImportExportPluginInterface::parseVCard(const QByteArray &data) const
{
    KContacts::VCardConverter converter;
    return converter.parseVCards(data);
}

KContacts::Addressee::List VCardImportExportPluginInterface::filterContacts(const KContacts::Addressee::List &addrList, KAddressBookImportExport::KAddressBookExportSelectionWidget::ExportFields exportFieldType) const
{
    KContacts::Addressee::List list;

    if (addrList.isEmpty()) {
        return addrList;
    }

    KContacts::Addressee::List::ConstIterator it;
    KContacts::Addressee::List::ConstIterator end(addrList.end());
    for (it = addrList.begin(); it != end; ++it) {
        KContacts::Addressee addr;

        addr.setUid((*it).uid());
        addr.setFormattedName((*it).formattedName());

        bool addrDone = false;
        if (exportFieldType & KAddressBookImportExport::KAddressBookExportSelectionWidget::DiplayName) {                  // output display name as N field
            QString fmtName = (*it).formattedName();
            QStringList splitNames = fmtName.split(QLatin1Char(' '), QString::SkipEmptyParts);
            if (splitNames.count() >= 2) {
                addr.setPrefix(QString());
                addr.setGivenName(splitNames.takeFirst());
                addr.setFamilyName(splitNames.takeLast());
                addr.setAdditionalName(splitNames.join(QLatin1Char(' ')));
                addr.setSuffix(QString());
                addrDone = true;
            }
        }

        if (!addrDone) {                                  // not wanted, or could not be split
            addr.setPrefix((*it).prefix());
            addr.setGivenName((*it).givenName());
            addr.setAdditionalName((*it).additionalName());
            addr.setFamilyName((*it).familyName());
            addr.setSuffix((*it).suffix());
        }

        addr.setExtraNickNameList((*it).extraNickNameList());
        addr.setMailer((*it).mailer());
        addr.setTimeZone((*it).timeZone());
        addr.setGeo((*it).geo());
        addr.setProductId((*it).productId());
        addr.setSortString((*it).sortString());
        addr.setUrl((*it).url());
        addr.setExtraUrlList((*it).extraUrlList());
        addr.setSecrecy((*it).secrecy());
        addr.setSound((*it).sound());
        addr.setEmailList((*it).emailList());
        addr.setCategories((*it).categories());
        addr.setExtraSoundList((*it).extraSoundList());
        addr.setGender((*it).gender());
        addr.setLangs((*it).langs());
        addr.setKind((*it).kind());
        addr.setMembers((*it).members());
        addr.setRelationShips((*it).relationShips());
        addr.setSourcesUrlList((*it).sourcesUrlList());
        addr.setImppList((*it).imppList());
        addr.setFieldGroupList((*it).fieldGroupList());

        if (exportFieldType & KAddressBookImportExport::KAddressBookExportSelectionWidget::Private) {
            addr.setBirthday((*it).birthday());
            addr.setNote((*it).note());
        }

        if (exportFieldType & KAddressBookImportExport::KAddressBookExportSelectionWidget::Picture) {
            if (exportFieldType & KAddressBookImportExport::KAddressBookExportSelectionWidget::Private) {
                addr.setPhoto((*it).photo());
                addr.setExtraPhotoList((*it).extraPhotoList());
            }

            if (exportFieldType & KAddressBookImportExport::KAddressBookExportSelectionWidget::Business) {
                addr.setLogo((*it).logo());
                addr.setExtraLogoList((*it).extraLogoList());
            }
        }

        if (exportFieldType & KAddressBookImportExport::KAddressBookExportSelectionWidget::Business) {
            addr.setExtraTitleList((*it).extraTitleList());
            addr.setExtraRoleList((*it).extraRoleList());
            addr.setExtraOrganizationList((*it).extraOrganizationList());
            addr.setDepartment((*it).department());

            KContacts::PhoneNumber::List phones = (*it).phoneNumbers(KContacts::PhoneNumber::Work);
            KContacts::PhoneNumber::List::Iterator phoneIt;
            KContacts::PhoneNumber::List::Iterator phoneEnd(phones.end());
            for (phoneIt = phones.begin(); phoneIt != phoneEnd; ++phoneIt) {
                addr.insertPhoneNumber(*phoneIt);
            }

            KContacts::Address::List addresses = (*it).addresses(KContacts::Address::Work);
            KContacts::Address::List::Iterator addrIt;
            KContacts::Address::List::Iterator addrEnd(addresses.end());
            for (addrIt = addresses.begin(); addrIt != addrEnd; ++addrIt) {
                addr.insertAddress(*addrIt);
            }
        }

        KContacts::PhoneNumber::List phones = (*it).phoneNumbers();
        KContacts::PhoneNumber::List::Iterator phoneIt;
        KContacts::PhoneNumber::List::Iterator phoneEnd(phones.end());
        for (phoneIt = phones.begin(); phoneIt != phoneEnd; ++phoneIt) {
            int phoneType = (*phoneIt).type();

            if ((phoneType & KContacts::PhoneNumber::Home) && (exportFieldType & KAddressBookImportExport::KAddressBookExportSelectionWidget::Private)) {
                addr.insertPhoneNumber(*phoneIt);
            } else if ((phoneType & KContacts::PhoneNumber::Work) && (exportFieldType & KAddressBookImportExport::KAddressBookExportSelectionWidget::Business)) {
                addr.insertPhoneNumber(*phoneIt);
            } else if ((exportFieldType & KAddressBookImportExport::KAddressBookExportSelectionWidget::Other)) {
                addr.insertPhoneNumber(*phoneIt);
            }
        }

        KContacts::Address::List addresses = (*it).addresses();
        KContacts::Address::List::Iterator addrIt;
        KContacts::Address::List::Iterator addrEnd(addresses.end());
        for (addrIt = addresses.begin(); addrIt != addrEnd; ++addrIt) {
            int addressType = (*addrIt).type();

            if ((addressType & KContacts::Address::Home) && exportFieldType & KAddressBookImportExport::KAddressBookExportSelectionWidget::Private) {
                addr.insertAddress(*addrIt);
            } else if ((addressType & KContacts::Address::Work) && (exportFieldType & KAddressBookImportExport::KAddressBookExportSelectionWidget::Business)) {
                addr.insertAddress(*addrIt);
            } else if (exportFieldType & KAddressBookImportExport::KAddressBookExportSelectionWidget::Other) {
                addr.insertAddress(*addrIt);
            }
        }

        if (exportFieldType & KAddressBookImportExport::KAddressBookExportSelectionWidget::Other) {
            addr.setCustoms((*it).customs());
        }

        if (exportFieldType & KAddressBookImportExport::KAddressBookExportSelectionWidget::Encryption) {
            addKey(addr, KContacts::Key::PGP);
            addKey(addr, KContacts::Key::X509);
        }

        list.append(addr);
    }

    return list;
}

void VCardImportExportPluginInterface::addKey(KContacts::Addressee &addr, KContacts::Key::Type type) const
{
#ifdef QGPGME_FOUND
    const QString fingerprint = addr.custom(QStringLiteral("KADDRESSBOOK"),
                                            (type == KContacts::Key::PGP ? QStringLiteral("OPENPGPFP") : QStringLiteral("SMIMEFP")));
    if (fingerprint.isEmpty()) {
        return;
    }

    GpgME::Context *context = GpgME::Context::createForProtocol(GpgME::OpenPGP);
    if (!context) {
        qCritical() << "No context available";
        return;
    }

    context->setArmor(false);
    context->setTextMode(false);

    QGpgME::QByteArrayDataProvider dataProvider;
    GpgME::Data dataObj(&dataProvider);
    GpgME::Error error = context->exportPublicKeys(fingerprint.toLatin1(), dataObj);
    delete context;

    if (error) {
        qCritical() << error.asString();
        return;
    }

    KContacts::Key key;
    key.setType(type);
    key.setBinaryData(dataProvider.data());

    addr.insertKey(key);
#else
    return;
#endif
}


void VCardImportExportPluginInterface::exportVCard()
{
    QPointer<KAddressBookImportExport::KAddressBookContactSelectionDialog> dlg =
        new KAddressBookImportExport::KAddressBookContactSelectionDialog(itemSelectionModel(), true, parentWidget());
    dlg->setMessageText(i18n("Which contact do you want to export?"));
    dlg->setDefaultAddressBook(defaultCollection());
    if (!dlg->exec() || !dlg) {
        delete dlg;
        return;
    }

    const KContacts::AddresseeList contacts = dlg->selectedContacts().addressList();
    const KAddressBookImportExport::KAddressBookExportSelectionWidget::ExportFields exportFields = dlg->exportType();
    delete dlg;

    if (contacts.isEmpty()) {
        KMessageBox::sorry(Q_NULLPTR, i18n("You have not selected any contacts to export."));
        return;
    }
}


bool VCardImportExportPluginInterface::canImportFileType(const QUrl &url)
{
    return url.path().endsWith(QStringLiteral(".vcf"));
}
