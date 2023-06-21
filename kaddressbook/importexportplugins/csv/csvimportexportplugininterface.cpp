/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "csvimportexportplugininterface.h"
#include "import/csvimportdialog.h"
#include <KActionCollection>
#include <KIO/Job>
#include <KJobWidgets>
#include <KLocalizedString>
#include <KMessageBox>
#include <PimCommon/RenameFileDialog>
#include <QAction>
#include <QFileDialog>
#include <QFileInfo>
#include <QPointer>
#include <QTemporaryFile>
#include <QTextCodec>
#include <QTextStream>

#include <KAddressBookImportExport/ContactSelectionDialog>
#include <KAddressBookImportExport/ImportExportEngine>

CSVImportExportPluginInterface::CSVImportExportPluginInterface(QObject *parent)
    : KAddressBookImportExport::PluginInterface(parent)
{
}

CSVImportExportPluginInterface::~CSVImportExportPluginInterface() = default;

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
    switch (mImportExportAction) {
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
    KAddressBookImportExport::ContactList contactList;
    QPointer<CSVImportDialog> dlg = new CSVImportDialog(parentWidget());
    if (dlg->exec()) {
        contactList.setAddressList(dlg->contacts());
    }

    delete dlg;
    auto engine = new KAddressBookImportExport::ImportExportEngine(this);
    engine->setContactList(contactList);
    engine->setDefaultAddressBook(defaultCollection());
    engine->importContacts();
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
    QTextStream stream(file);
    stream.setEncoding(QStringConverter::System);

    auto fields = KAddressBookImportExport::ContactFields::allFields();
    fields.remove(KAddressBookImportExport::ContactFields::Undefined);

    bool first = true;

    // First output the column headings
    const int fieldsCount(fields.count());
    for (int i = 0; i < fieldsCount; ++i) {
        if (!first) {
            stream << ",";
        }

        // add quoting as defined in RFC 4180
        QString label = KAddressBookImportExport::ContactFields::label(fields.at(i));
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
            if (fields.at(j) == KAddressBookImportExport::ContactFields::Birthday || fields.at(j) == KAddressBookImportExport::ContactFields::Anniversary) {
                const QDateTime dateTime = QDateTime::fromString(KAddressBookImportExport::ContactFields::value(fields.at(j), contact), Qt::ISODate);
                if (dateTime.isValid()) {
                    content = dateTime.date().toString(Qt::ISODate);
                }
            } else {
                content = KAddressBookImportExport::ContactFields::value(fields.at(j), contact).replace(QLatin1Char('\n'), QStringLiteral("\\n"));
            }

            // add quoting as defined in RFC 4180
            content.replace(QLatin1Char('"'), QStringLiteral("\"\""));

            stream << '\"' << content << '\"';
            first = false;
        }

        stream << "\n";
    }
}

void CSVImportExportPluginInterface::exportCSV()
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
    QUrl url = QFileDialog::getSaveFileUrl(parentWidget(), QString(), QUrl::fromLocalFile(QStringLiteral("addressbook.csv")), QString(), nullptr, options);
    if (url.isEmpty()) {
        return;
    }

    if (QFileInfo::exists(url.isLocalFile() ? url.toLocalFile() : url.path())) {
        if (url.isLocalFile() && QFileInfo::exists(url.toLocalFile())) {
            auto dialog = new PimCommon::RenameFileDialog(url, false, parentWidget());
            auto result = static_cast<PimCommon::RenameFileDialog::RenameFileDialogResult>(dialog->exec());
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
        exportToFile(&tmpFile, contactLists.addressList());
        tmpFile.flush();
        auto job = KIO::file_copy(QUrl::fromLocalFile(tmpFile.fileName()), url, -1, KIO::Overwrite);
        KJobWidgets::setWindow(job, parentWidget());
        job->exec();
    } else {
        QFile file(url.toLocalFile());
        if (!file.open(QIODevice::WriteOnly)) {
            const QString msg = i18n("<qt>Unable to open file <b>%1</b>.</qt>", url.toLocalFile());
            KMessageBox::error(parentWidget(), msg);
            return;
        }

        exportToFile(&file, contactLists.addressList());
        file.close();
    }
}

bool CSVImportExportPluginInterface::canImportFileType(const QUrl &url)
{
    return url.path().endsWith(QLatin1String(".csv"));
}

void CSVImportExportPluginInterface::importFile(const QUrl &url)
{
    // TODO
    Q_UNUSED(url)
}

#include "moc_csvimportexportplugininterface.cpp"
