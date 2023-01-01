/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "windowscontactimportexportplugininterface.h"
#include "importexportwindowscontactplugin_debug.h"
#include "importwindowcontact.h"
#include <KActionCollection>
#include <KLocalizedString>
#include <PimCommon/RenameFileDialog>
#include <QAction>
#include <QFile>
#include <QFileDialog>

#include <KAddressBookImportExport/ImportExportEngine>

WindowsContactImportExportPluginInterface::WindowsContactImportExportPluginInterface(QObject *parent)
    : KAddressBookImportExport::PluginInterface(parent)
{
}

WindowsContactImportExportPluginInterface::~WindowsContactImportExportPluginInterface() = default;

void WindowsContactImportExportPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = ac->addAction(QStringLiteral("file_import_windows_contact"));
    action->setText(i18n("Import Windows Contact file..."));
    action->setWhatsThis(i18n("Import contacts from windows contact file."));
    setImportActions(QList<QAction *>() << action);
    connect(action, &QAction::triggered, this, &WindowsContactImportExportPluginInterface::slotImportWindowsContact);

    // If a day we implement it
    //    action = ac->addAction(QStringLiteral("file_export_windows_contact"));
    //    action->setText(i18n("Export Windows Contact file..."));
    //    action->setWhatsThis(i18n("Export contacts to windows contact file."));
    //    setExportActions(QList<QAction *>() << action);
    //    connect(action, &QAction::triggered, this, &WindowsContactImportExportPluginInterface::slotExportWindowsContact);
}

void WindowsContactImportExportPluginInterface::slotExportWindowsContact()
{
    mImportExportAction = Export;
    Q_EMIT emitPluginActivated(this);
}

void WindowsContactImportExportPluginInterface::slotImportWindowsContact()
{
    mImportExportAction = Import;
    Q_EMIT emitPluginActivated(this);
}

void WindowsContactImportExportPluginInterface::exec()
{
    switch (mImportExportAction) {
    case Import:
        importWindowsContact();
        break;
    case Export:
        exportWindowsContact();
        break;
    }
}

void WindowsContactImportExportPluginInterface::importWindowsContact()
{
    const QStringList fileNames = QFileDialog::getOpenFileNames(parentWidget(), QString(), QDir::homePath(), i18n("Windows Contact file (*.contact)"));

    if (fileNames.isEmpty()) {
        return;
    }

    KContacts::Addressee::List addresseeList;
    ImportWindowContact importer;
    importer.setParentWidget(parentWidget());
    for (const QString &fileName : fileNames) {
        addresseeList.append(importer.importFile(fileName));
    }

    KAddressBookImportExport::ContactList contactList;
    contactList.setAddressList(addresseeList);

    auto engine = new KAddressBookImportExport::ImportExportEngine(this);
    engine->setContactList(contactList);
    engine->setDefaultAddressBook(defaultCollection());
    engine->importContacts();
}

void WindowsContactImportExportPluginInterface::exportWindowsContact()
{
    qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << "Export windows contact not implement yet";
    // TODO
}

bool WindowsContactImportExportPluginInterface::canImportFileType(const QUrl &url)
{
    return url.path().endsWith(QLatin1String(".contact"));
}

void WindowsContactImportExportPluginInterface::importFile(const QUrl &url)
{
    Q_UNUSED(url)
}
