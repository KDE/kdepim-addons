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

#include "gmximportexportplugininterface.h"
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>

GMXImportExportPluginInterface::GMXImportExportPluginInterface(QObject *parent)
    : KAddressBookImportExport::KAddressBookImportExportPluginInterface(parent)
{

}

GMXImportExportPluginInterface::~GMXImportExportPluginInterface()
{

}


void GMXImportExportPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = ac->addAction(QStringLiteral("file_import_gmx"));
    action->setText(i18n("Import GMX file..."));
    action->setWhatsThis(i18n("Import contacts from a GMX address book file."));
    setImportActions(QList<QAction *>() << action);
    connect(action, &QAction::triggered, this, &GMXImportExportPluginInterface::slotImportGmx);

    action = ac->addAction(QStringLiteral("file_export_gmx"));
    action->setText(i18n("Export GMX file..."));
    action->setWhatsThis(i18n("Export contacts to a GMX address book file."));
    setExportActions(QList<QAction *>() << action);
    connect(action, &QAction::triggered, this, &GMXImportExportPluginInterface::slotExportGmx);
}

void GMXImportExportPluginInterface::exec()
{
    switch(mImportExportAction) {
    case Import:
        break;
    case Export:
        break;
    }
    //TODO
}

void GMXImportExportPluginInterface::slotImportGmx()
{
    mImportExportAction = Import;
    Q_EMIT emitPluginActivated(this);
}

void GMXImportExportPluginInterface::slotExportGmx()
{
    mImportExportAction = Export;
    Q_EMIT emitPluginActivated(this);
}
