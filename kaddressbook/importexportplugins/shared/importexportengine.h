/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

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
