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

#include "ldifimportexportplugininterface.h"
#include "../shared/importexportengine.h"
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <KMessageBox>
#include <KContacts/LDIFConverter>
#include <KAddressBookImportExport/KAddressBookImportExportContactList>

LDifImportExportPluginInterface::LDifImportExportPluginInterface(QObject *parent)
    : KAddressBookImportExport::KAddressBookImportExportPluginInterface(parent),
      mEngine(Q_NULLPTR)
{

}

LDifImportExportPluginInterface::~LDifImportExportPluginInterface()
{

}


void LDifImportExportPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = ac->addAction(QStringLiteral("file_import_ldif"));
    action->setText(i18n("Import LDIF file..."));
    action->setWhatsThis(i18n("Import contacts from an LDIF file."));
    connect(action, &QAction::triggered, this, &LDifImportExportPluginInterface::slotImportLdif);
    setImportActions(QList<QAction *>() << action);

    action = ac->addAction(QStringLiteral("file_export_ldif"));
    action->setText(i18n("Export LDIF file..."));
    action->setWhatsThis(i18n("Export contacts to an LDIF file."));
    connect(action, &QAction::triggered, this, &LDifImportExportPluginInterface::slotExportLdif);
    setExportActions(QList<QAction *>() << action);
}

void LDifImportExportPluginInterface::exec()
{
    switch(mImportExportAction) {
    case Import:
        import();
        break;
    case Export:
        break;
    }
    //TODO
}

void LDifImportExportPluginInterface::slotImportLdif()
{
    mImportExportAction = Import;
    Q_EMIT emitPluginActivated(this);
}

void LDifImportExportPluginInterface::slotExportLdif()
{
    mImportExportAction = Export;
    Q_EMIT emitPluginActivated(this);
}


void LDifImportExportPluginInterface::import()
{
    KAddressBookImportExport::KAddressBookImportExportContactList contactList;
    const QString fileName = QFileDialog::getOpenFileName(parentWidget(), QString(),  QDir::homePath(), i18n("LDif Files (*.ldif)"));
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
    stream.setCodec("ISO 8859-1");

    const QString wholeFile = stream.readAll();
    const QDateTime dtDefault = QFileInfo(file).lastModified();
    file.close();
    KContacts::ContactGroup::List lstGroup;
    KContacts::Addressee::List lstAddresses;
    KContacts::LDIFConverter::LDIFToAddressee(wholeFile, lstAddresses, lstGroup, dtDefault);
    contactList.setAddressList(lstAddresses);
    contactList.setContactGroupList(lstGroup);

    if (!mEngine) {
        mEngine = new ImportExportEngine(this);
    }
    mEngine->setContactList(contactList);
    mEngine->setDefaultAddressBook(defaultCollection());
    connect(mEngine, &ImportExportEngine::finished, this, &LDifImportExportPluginInterface::slotFinished);
    mEngine->importContacts();
}

void LDifImportExportPluginInterface::slotFinished()
{
    mEngine->deleteLater();
    mEngine = Q_NULLPTR;
}
