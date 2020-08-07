/*
   Copyright (C) 2020 Laurent Montel <montel@kde.org>

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

#include "windowscontactimportexportplugininterface.h"
#include "../shared/importexportengine.h"
#include "importexportwindowscontactplugin_debug.h"
#include "importwindowcontact.h"
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>
#include <QFileInfo>
#include <QTemporaryFile>
#include <PimCommon/RenameFileDialog>
#include <KMessageBox>
#include <KJobWidgets>
#include <QTextStream>
#include <QFileDialog>
#include <QTextCodec>
#include <QPointer>
#include <KAddressBookContactSelectionDialog>
#include <QFile>
#include <QDomElement>
#include <KIO/Job>

WindowsContactImportExportPluginInterface::WindowsContactImportExportPluginInterface(QObject *parent)
    : KAddressBookImportExport::KAddressBookImportExportPluginInterface(parent)
{
}

WindowsContactImportExportPluginInterface::~WindowsContactImportExportPluginInterface()
{
}

void WindowsContactImportExportPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = ac->addAction(QStringLiteral("file_import_windows_contact"));
    action->setText(i18n("Import Windows Contact file..."));
    action->setWhatsThis(i18n("Import contacts from windows contact file."));
    setImportActions(QList<QAction *>() << action);
    connect(action, &QAction::triggered, this, &WindowsContactImportExportPluginInterface::slotImportWindowsContact);

    //If a day we implement it
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
    const QStringList fileNames
        = QFileDialog::getOpenFileNames(parentWidget(), QString(), QDir::homePath(), i18n("Windows Contact file (*.contact)"));

    if (fileNames.isEmpty()) {
        return;
    }

    KContacts::Addressee::List addresseeList;
    ImportWindowContact importer;
    importer.setParentWidget(parentWidget());
    for (const QString &fileName : fileNames) {
        addresseeList.append(importer.importFile(fileName));
    }

    KAddressBookImportExport::KAddressBookImportExportContactList contactList;
    contactList.setAddressList(addresseeList);

    ImportExportEngine *engine = new ImportExportEngine(this);
    engine->setContactList(contactList);
    engine->setDefaultAddressBook(defaultCollection());
    engine->importContacts();
}

void WindowsContactImportExportPluginInterface::exportWindowsContact()
{
    qCWarning(IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG) << "Export windows contact not implement yet";
    //TODO
}

bool WindowsContactImportExportPluginInterface::canImportFileType(const QUrl &url)
{
    return url.path().endsWith(QLatin1String(".contact"));
}

void WindowsContactImportExportPluginInterface::importFile(const QUrl &url)
{
    Q_UNUSED(url);
}
