/*
   Copyright (C) 2016-2020 Laurent Montel <montel@kde.org>

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
//    QAction *action = ac->addAction(QStringLiteral("file_export_csv"));
//    action->setText(i18n("Export CSV file..."));
//    action->setWhatsThis(i18n("Export contacts to a file in comma separated value format."));
//    setExportActions(QList<QAction *>() << action);
//    connect(action, &QAction::triggered, this, &WindowsContactImportExportPluginInterface::slotExportCVS);

//    action = ac->addAction(QStringLiteral("file_import_csv"));
//    action->setText(i18n("Import CSV file..."));
//    action->setWhatsThis(i18n("Import contacts from a file in comma separated value format."));
//    setImportActions(QList<QAction *>() << action);
//    connect(action, &QAction::triggered, this, &WindowsContactImportExportPluginInterface::slotImportCVS);
}

void WindowsContactImportExportPluginInterface::exec()
{
//    switch (mImportExportAction) {
//    case Import:
//        importCSV();
//        break;
//    case Export:
//        exportCSV();
//        break;
    //    }
}

bool WindowsContactImportExportPluginInterface::canImportFileType(const QUrl &url)
{
    //TODO
    return false;
}

void WindowsContactImportExportPluginInterface::importFile(const QUrl &url)
{
    //TODO
}


