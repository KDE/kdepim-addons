/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ldapimportexportplugininterface.h"
#include <KActionCollection>
#include <KAddressBookImportExport/ImportExportEngine>
#include <KLocalizedString>
#include <PimCommonAkonadi/LdapSearchDialog>
#include <QAction>
#include <QPointer>
using namespace Qt::Literals::StringLiterals;

LDapImportExportPluginInterface::LDapImportExportPluginInterface(QObject *parent)
    : KAddressBookImportExport::PluginInterface(parent)
{
}

LDapImportExportPluginInterface::~LDapImportExportPluginInterface() = default;

void LDapImportExportPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = ac->addAction(u"file_import_ldap"_s);
    action->setText(i18n("Import From LDAP server…"));
    action->setWhatsThis(i18n("Import contacts from an LDAP server."));
    setImportActions({action});
    connect(action, &QAction::triggered, this, &LDapImportExportPluginInterface::slotImportLdap);
}

void LDapImportExportPluginInterface::exec()
{
    switch (mImportExportAction) {
    case ImportExportAction::Import:
        importLdap();
        break;
    case ImportExportAction::Export:
        break;
    }
}

void LDapImportExportPluginInterface::slotImportLdap()
{
    mImportExportAction = ImportExportAction::Import;
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
