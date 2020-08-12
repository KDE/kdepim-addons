/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef IMPORTEXPORTENGINE_H
#define IMPORTEXPORTENGINE_H

#include <QObject>
#include "kaddressbookimportexportlibprivate_export.h"
#include <KAddressBookImportExport/KAddressBookImportExportContactList>
#include <AkonadiCore/Collection>
class QProgressDialog;
class KJob;
class KADDRESSBOOKIMPORTEXPORTLIBPRIVATE_EXPORT ImportExportEngine : public QObject
{
    Q_OBJECT
public:
    explicit ImportExportEngine(QObject *parent = nullptr);
    ~ImportExportEngine();
    void setContactList(const KAddressBookImportExport::KAddressBookImportExportContactList &contacts);

    void importContacts();
    void setParentWidget(QWidget *parent);
    QWidget *parentWidget() const;
    void setDefaultAddressBook(const Akonadi::Collection &defaultAddressBook);

Q_SIGNALS:
    void finished();

private:
    void slotImportJobDone(KJob *);
    KAddressBookImportExport::KAddressBookImportExportContactList mContactsList;
    Akonadi::Collection mDefaultAddressBook;
    QWidget *mParentWidget = nullptr;
    QProgressDialog *mImportProgressDialog = nullptr;
    int mNumberElementToImport = -1;
    int mImportDone = 0;
};

#endif // IMPORTEXPORTENGINE_H
