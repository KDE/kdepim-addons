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

#include "csvimportexportplugininterface.h"
#include "../shared/importexportengine.h"
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
#include <KIO/Job>

CSVImportExportPluginInterface::CSVImportExportPluginInterface(QObject *parent)
    : KAddressBookImportExport::KAddressBookImportExportPluginInterface(parent),
      mEngine(Q_NULLPTR)
{

}

CSVImportExportPluginInterface::~CSVImportExportPluginInterface()
{

}


void CSVImportExportPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = ac->addAction(QStringLiteral("file_export_csv"));
    action->setText(i18n("Export CSV file..."));
    action->setWhatsThis(i18n("Export contacts to a file in comma separated value format."));
    setExportActions(QList<QAction *>() << action);
    connect(action, &QAction::triggered, this, &CSVImportExportPluginInterface::slotExportCVS);

    action = ac->addAction(QStringLiteral("file_import_csv"));
    action->setText(i18n("Import CSV file..."));
    action->setWhatsThis(i18n("Import contacts from a file in comma separated value format."));
    setImportActions(QList<QAction *>() << action);
    connect(action, &QAction::triggered, this, &CSVImportExportPluginInterface::slotImportCVS);
}


void CSVImportExportPluginInterface::exec()
{
    switch(mImportExportAction) {
    case Import:
        importCSV();
        break;
    case Export:
        exportCSV();
        break;
    }
}

void CSVImportExportPluginInterface::importCSV()
{
#if 0
    KAddressBookImportExport::KAddressBookImportExportContactList contactList;
    QPointer<CSVImportDialog> dlg = new CSVImportDialog(parentWidget());
    if (dlg->exec() && dlg) {
        contactList.setAddressList(dlg->contacts());
    }

    delete dlg;
    if (!mEngine) {
        mEngine = new ImportExportEngine(this);
    }
    mEngine->setContactList(contactList);
    mEngine->setDefaultAddressBook(defaultCollection());
    connect(mEngine, &ImportExportEngine::finished, this, &CSVImportExportPluginInterface::slotFinished);
    mEngine->importContacts();
#endif
}

void CSVImportExportPluginInterface::slotFinished()
{
    mEngine->deleteLater();
    mEngine = Q_NULLPTR;
}


void CSVImportExportPluginInterface::slotImportCVS()
{
    mImportExportAction = Import;
    Q_EMIT emitPluginActivated(this);
}

void CSVImportExportPluginInterface::slotExportCVS()
{
    mImportExportAction = Export;
    Q_EMIT emitPluginActivated(this);
}

void CSVImportExportPluginInterface::exportToFile(QFile *file, const KContacts::Addressee::List &contacts) const
{
#if 0 //FIXME
    QTextStream stream(file);
    stream.setCodec(QTextCodec::codecForLocale());

    ContactFields::Fields fields = ContactFields::allFields();
    fields.remove(ContactFields::Undefined);

    bool first = true;

    // First output the column headings
    for (int i = 0; i < fields.count(); ++i) {
        if (!first) {
            stream << ",";
        }

        // add quoting as defined in RFC 4180
        QString label = ContactFields::label(fields.at(i));
        label.replace(QLatin1Char('"'), QStringLiteral("\"\""));

        stream << "\"" << label << "\"";
        first = false;
    }
    stream << "\n";

    // Then all the contacts
    for (int i = 0; i < contacts.count(); ++i) {

        const KContacts::Addressee contact = contacts.at(i);
        first = true;

        for (int j = 0; j < fields.count(); ++j) {
            if (!first) {
                stream << ",";
            }

            QString content;
            if (fields.at(j) == ContactFields::Birthday ||
                    fields.at(j) == ContactFields::Anniversary) {
                const QDateTime dateTime =
                    QDateTime::fromString(ContactFields::value(fields.at(j), contact), Qt::ISODate);
                if (dateTime.isValid()) {
                    content = dateTime.date().toString(Qt::ISODate);
                }
            } else {
                content = ContactFields::value(fields.at(j), contact).replace(QLatin1Char('\n'), QStringLiteral("\\n"));
            }

            // add quoting as defined in RFC 4180
            content.replace(QLatin1Char('"'), QStringLiteral("\"\""));

            stream << '\"' << content << '\"';
            first = false;
        }

        stream << "\n";
    }
#endif
}

void CSVImportExportPluginInterface::exportCSV()
{
    QUrl url = QFileDialog::getSaveFileUrl(parentWidget(), QString(), QUrl::fromLocalFile(QStringLiteral("addressbook.csv")));
    if (url.isEmpty()) {
        return;
    }

    if (QFileInfo(url.isLocalFile() ? url.toLocalFile() : url.path()).exists()) {
        if (url.isLocalFile() && QFileInfo(url.toLocalFile()).exists()) {
            PimCommon::RenameFileDialog::RenameFileDialogResult result = PimCommon::RenameFileDialog::RENAMEFILE_IGNORE;
            PimCommon::RenameFileDialog *dialog = new PimCommon::RenameFileDialog(url, false, parentWidget());
            result = static_cast<PimCommon::RenameFileDialog::RenameFileDialogResult>(dialog->exec());
            if (result == PimCommon::RenameFileDialog::RENAMEFILE_RENAME) {
                url = dialog->newName();
            } else if (result == PimCommon::RenameFileDialog::RENAMEFILE_IGNORE) {
                delete dialog;
                return;
            }
            delete dialog;
        }
    }

    if (!url.isLocalFile()) {
        QTemporaryFile tmpFile;
        if (!tmpFile.open()) {
            const QString msg = i18n("<qt>Unable to open file <b>%1</b></qt>", url.url());
            KMessageBox::error(parentWidget(), msg);
            return;
        }
#if 0 //FIXME
        exportToFile(&tmpFile, contacts.addressList());
        tmpFile.flush();
        auto job = KIO::file_copy(QUrl::fromLocalFile(tmpFile.fileName()), url, -1, KIO::Overwrite);
        KJobWidgets::setWindow(job, parentWidget());
        job->exec();
#endif
    } else {
        QFile file(url.toLocalFile());
        if (!file.open(QIODevice::WriteOnly)) {
            const QString msg = i18n("<qt>Unable to open file <b>%1</b>.</qt>", url.toLocalFile());
            KMessageBox::error(parentWidget(), msg);
            return;
        }

        //FIXME exportToFile(&file, contacts.addressList());
        file.close();

    }
}
