/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ldifimportexportplugininterface.h"
#include <KActionCollection>
#include <KContacts/LDIFConverter>
#include <KJobWidgets>
#include <KLocalizedString>
#include <KMessageBox>
#include <PimCommon/RenameFileDialog>
#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QPointer>
#include <QTemporaryFile>
#include <QTextStream>
#include <kio/filecopyjob.h>

#include <KAddressBookImportExport/ContactList>
#include <KAddressBookImportExport/ContactSelectionDialog>
#include <KAddressBookImportExport/ImportExportEngine>

LDifImportExportPluginInterface::LDifImportExportPluginInterface(QObject *parent)
    : KAddressBookImportExport::PluginInterface(parent)
{
}

LDifImportExportPluginInterface::~LDifImportExportPluginInterface() = default;

void LDifImportExportPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = ac->addAction(QStringLiteral("file_import_ldif"));
    action->setText(i18n("Import LDIF file…"));
    action->setWhatsThis(i18n("Import contacts from an LDIF file."));
    connect(action, &QAction::triggered, this, &LDifImportExportPluginInterface::slotImportLdif);
    setImportActions(QList<QAction *>() << action);

    action = ac->addAction(QStringLiteral("file_export_ldif"));
    action->setText(i18n("Export LDIF file…"));
    action->setWhatsThis(i18n("Export contacts to an LDIF file."));
    connect(action, &QAction::triggered, this, &LDifImportExportPluginInterface::slotExportLdif);
    setExportActions(QList<QAction *>() << action);
}

void LDifImportExportPluginInterface::exec()
{
    switch (mImportExportAction) {
    case ImportExportAction::Import:
        importLdif();
        break;
    case ImportExportAction::Export:
        exportLdif();
        break;
    }
}

void LDifImportExportPluginInterface::slotImportLdif()
{
    mImportExportAction = ImportExportAction::Import;
    Q_EMIT emitPluginActivated(this);
}

void LDifImportExportPluginInterface::slotExportLdif()
{
    mImportExportAction = ImportExportAction::Export;
    Q_EMIT emitPluginActivated(this);
}

void LDifImportExportPluginInterface::importLdifFile(const QString &fileName)
{
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        const QString msg = i18n("<qt>Unable to open <b>%1</b> for reading.</qt>", fileName);
        KMessageBox::error(parentWidget(), msg);
        return;
    }

    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Latin1);

    const QString wholeFile = stream.readAll();
    const QDateTime dtDefault = QFileInfo(file).lastModified();
    file.close();
    KContacts::ContactGroup::List lstGroup;
    KContacts::Addressee::List lstAddresses;
    KContacts::LDIFConverter::LDIFToAddressee(wholeFile, lstAddresses, lstGroup, dtDefault);
    KAddressBookImportExport::ContactList contactList;
    contactList.setAddressList(lstAddresses);
    contactList.setContactGroupList(lstGroup);

    auto engine = new KAddressBookImportExport::ImportExportEngine(this);
    engine->setContactList(contactList);
    engine->setDefaultAddressBook(defaultCollection());
    engine->importContacts();
}

void LDifImportExportPluginInterface::importLdif()
{
    const QString fileName = QFileDialog::getOpenFileName(parentWidget(), QString(), QDir::homePath(), QStringLiteral("%1 (*.ldif)").arg(i18n("LDif Files")));
    importLdifFile(fileName);
}

void doExport(QFile *file, const KAddressBookImportExport::ContactList &list)
{
    QString data;
    KContacts::LDIFConverter::addresseeAndContactGroupToLDIF(list.addressList(), list.contactGroupList(), data);

    QTextStream stream(file);
    stream << data;
}

void LDifImportExportPluginInterface::exportLdif()
{
    QPointer<KAddressBookImportExport::ContactSelectionDialog> dlg =
        new KAddressBookImportExport::ContactSelectionDialog(itemSelectionModel(), false, parentWidget());
    dlg->setMessageText(i18n("Which contact do you want to export?"));
    dlg->setDefaultAddressBook(defaultCollection());
    if (!dlg->exec()) {
        delete dlg;
        return;
    }
    const KContacts::AddresseeList contacts = dlg->selectedContacts().addressList();
    delete dlg;

    if (contacts.isEmpty()) {
        KMessageBox::error(nullptr, i18n("You have not selected any contacts to export."));
        return;
    }

    KAddressBookImportExport::ContactList contactLists;
    contactLists.setAddressList(contacts);

    QFileDialog::Options options = QFileDialog::DontConfirmOverwrite;
    const QUrl url = QFileDialog::getSaveFileUrl(parentWidget(),
                                                 QString(),
                                                 QUrl::fromLocalFile(QDir::homePath() + QStringLiteral("/addressbook.ldif")),
                                                 i18n("LDif Files (*.ldif)"),
                                                 nullptr,
                                                 options);
    if (url.isEmpty()) {
        return;
    }

    if (!url.isLocalFile()) {
        QTemporaryFile tmpFile;
        if (!tmpFile.open()) {
            const QString msg = i18n("<qt>Unable to open file <b>%1</b></qt>", url.url());
            KMessageBox::error(parentWidget(), msg);
            return;
        }

        doExport(&tmpFile, contactLists);
        tmpFile.flush();
        auto job = KIO::file_copy(QUrl::fromLocalFile(tmpFile.fileName()), url, -1, KIO::Overwrite);
        KJobWidgets::setWindow(job, parentWidget());
        job->exec();
    } else {
        QString fileName = url.toLocalFile();

        if (QFileInfo::exists(fileName)) {
            if (url.isLocalFile() && QFileInfo::exists(url.toLocalFile())) {
                auto dialog = new PimCommon::RenameFileDialog(url, false, parentWidget());
                auto result = static_cast<PimCommon::RenameFileDialog::RenameFileDialogResult>(dialog->exec());
                if (result == PimCommon::RenameFileDialog::RENAMEFILE_RENAME) {
                    fileName = dialog->newName().toLocalFile();
                } else if (result == PimCommon::RenameFileDialog::RENAMEFILE_IGNORE) {
                    delete dialog;
                    return;
                }
                delete dialog;
            }
        }

        QFile file(fileName);

        if (!file.open(QIODevice::WriteOnly)) {
            const QString txt = i18n("<qt>Unable to open file <b>%1</b>.</qt>", fileName);
            KMessageBox::error(parentWidget(), txt);
            return;
        }
        QString data;
        KContacts::LDIFConverter::addresseeAndContactGroupToLDIF(contactLists.addressList(), contactLists.contactGroupList(), data);

        QTextStream stream(&file);
        stream << data;
        file.close();
    }
}

bool LDifImportExportPluginInterface::canImportFileType(const QUrl &url)
{
    return url.path().endsWith(QLatin1StringView(".ldif"));
}

void LDifImportExportPluginInterface::importFile(const QUrl &url)
{
    if (url.isLocalFile()) {
        importLdifFile(url.path());
    }
}

#include "moc_ldifimportexportplugininterface.cpp"
