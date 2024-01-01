/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ldapimportexportplugininterface.h"
#include <KActionCollection>
#include <KAddressBookImportExport/ImportExportEngine>
#include <KLocalizedString>
#include <PimCommonAkonadi/LdapSearchDialog>
#include <QAction>
#include <QPointer>

LDapImportExportPluginInterface::LDapImportExportPluginInterface(QObject *parent)
    : KAddressBookImportExport::PluginInterface(parent)
{
}

LDapImportExportPluginInterface::~LDapImportExportPluginInterface() = default;

void LDapImportExportPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = ac->addAction(QStringLiteral("file_import_ldap"));
    action->setText(i18n("Import From LDAP server..."));
    action->setWhatsThis(i18n("Import contacts from an LDAP server."));
    setImportActions({action});
    connect(action, &QAction::triggered, this, &LDapImportExportPluginInterface::slotImportLdap);
}

void LDapImportExportPluginInterface::exec()
{
    switch (mImportExportAction) {
    case Import:
        importLdap();
        break;
    case Export:
        break;
    }
}

void LDapImportExportPluginInterface::slotImportLdap()
{
    mImportExportAction = Import;
    Q_EMIT emitPluginActivated(this);
}

void LDapImportExportPluginInterface::importLdap()
{
    KAddressBookImportExport::ContactList contactList;
    QPointer<PimCommon::LdapSearchDialog> dlg = new PimCommon::LdapSearchDialog(parentWidget());

    if (dlg->exec()) {
        contactList.setAddressList(dlg->selectedContacts());
    }

    delete dlg;
    auto engine = new KAddressBookImportExport::ImportExportEngine(this);
    engine->setContactList(contactList);
    engine->setDefaultAddressBook(defaultCollection());
    engine->importContacts();
}

#include "moc_ldapimportexportplugininterface.cpp"
