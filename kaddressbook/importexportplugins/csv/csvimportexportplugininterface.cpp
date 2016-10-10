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
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>

CSVImportExportPluginInterface::CSVImportExportPluginInterface(QObject *parent)
    : KAddressBookImportExport::KAddressBookImportExportPluginInterface(parent)
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
        break;
    case Export:
        break;
    }
    //TODO
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
