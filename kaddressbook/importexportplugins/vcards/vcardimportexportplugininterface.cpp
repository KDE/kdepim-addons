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

VCardImportExportPluginInterface::VCardImportExportPluginInterface(QObject *parent)
    : KAddressBookImportExport::KAddressBookImportExportPluginInterface(parent)
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
    setImportActions(QList<QAction *>() << action);

    QList<QAction *> exportActionList;

    action = ac->addAction(QStringLiteral("file_export_vcard40"));
    action->setWhatsThis(i18n("Export contacts to a vCard 4.0 file."));
    action->setText(i18n("Export vCard 4.0..."));
    exportActionList << action;

    action = ac->addAction(QStringLiteral("file_export_vcard30"));
    action->setText(i18n("Export vCard 3.0..."));
    action->setWhatsThis(i18n("Export contacts to a vCard 3.0 file."));
    exportActionList << action;

    action = ac->addAction(QStringLiteral("file_export_vcard21"));
    action->setText(i18n("Export vCard 2.1..."));
    action->setWhatsThis(i18n("Export contacts to a vCard 2.1 file."));
    exportActionList << action;
    setExportActions(exportActionList);
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
