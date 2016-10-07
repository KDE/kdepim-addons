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
#if 0
    QAction *action = ac->addAction(QStringLiteral("file_import_gmx"));
    action->setText(i18n("Import GMX..."));
    action->setWhatsThis(i18n("Import contacts from a GMX file."));
    setImportActions(QList<QAction *>() << action);

    QList<QAction *> exportActionList;

    action = ac->addAction(QStringLiteral("file_import_gmx"));
    action->setText(i18n("Import GMX..."));
    action->setWhatsThis(i18n("Import contacts from a GMX file."));
    exportActionList << action;

    action = ac->addAction(QStringLiteral("file_export_gmx40"));
    action->setWhatsThis(i18n("Export contacts to a GMX 4.0 file."));
    action->setText(i18n("Export GMX 4.0..."));
    exportActionList << action;

    action = ac->addAction(QStringLiteral("file_export_gmx30"));
    action->setText(i18n("Export GMX 3.0..."));
    action->setWhatsThis(i18n("Export contacts to a GMX 3.0 file."));
    exportActionList << action;

    action = ac->addAction(QStringLiteral("file_export_gmx21"));
    action->setText(i18n("Export GMX 2.1..."));
    action->setWhatsThis(i18n("Export contacts to a GMX 2.1 file."));
    exportActionList << action;
    setExportActions(exportActionList);
#endif
}

void GMXImportExportPluginInterface::exec()
{
}
