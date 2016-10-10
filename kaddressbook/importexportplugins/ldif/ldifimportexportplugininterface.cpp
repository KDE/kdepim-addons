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
#include <KJobWidgets>
#include <PimCommon/RenameFileDialog>
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
        exportLdif();
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

void LDifImportExportPluginInterface::exportLdif()
{
#if 0
    const QUrl url =
        QFileDialog::getSaveFileUrl(parentWidget(), QString(), QUrl::fromLocalFile(QDir::homePath() + QLatin1String("/addressbook.ldif")), i18n("LDif Files (*.ldif)"));
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

        doExport(&tmpFile, list);
        tmpFile.flush();
        auto job = KIO::file_copy(QUrl::fromLocalFile(tmpFile.fileName()), url, -1, KIO::Overwrite);
        KJobWidgets::setWindow(job, parentWidget());
        job->exec();

    } else {
        QString fileName = url.toLocalFile();

        if (QFileInfo(fileName).exists()) {
            if (url.isLocalFile() && QFileInfo(url.toLocalFile()).exists()) {
                PimCommon::RenameFileDialog::RenameFileDialogResult result = PimCommon::RenameFileDialog::RENAMEFILE_IGNORE;
                PimCommon::RenameFileDialog *dialog = new PimCommon::RenameFileDialog(url, false, parentWidget());
                result = static_cast<PimCommon::RenameFileDialog::RenameFileDialogResult>(dialog->exec());
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
            QString txt = i18n("<qt>Unable to open file <b>%1</b>.</qt>", fileName);
            KMessageBox::error(parentWidget(), txt);
            return;
        }
        QString data;
        KContacts::LDIFConverter::addresseeAndContactGroupToLDIF(list.addressList(), list.contactGroupList(), data);

        QTextStream stream(file);
        stream.setCodec("UTF-8");
        stream << data;
        file.close();
    }
#endif
}

void LDifImportExportPluginInterface::slotFinished()
{
    mEngine->deleteLater();
    mEngine = Q_NULLPTR;
}
