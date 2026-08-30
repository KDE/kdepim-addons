/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactsplugininterface.h"

#include <KActionCollection>
#include <KLocalizedString>
#include <QAction>

#include "manualmerge/mergecontactsdialog.h"
using namespace Qt::Literals::StringLiterals;

MergeContactsPluginInterface::MergeContactsPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
{
}

MergeContactsPluginInterface::~MergeContactsPluginInterface() = default;

void MergeContactsPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = ac->addAction(u"merge_contacts"_s);
    action->setText(i18n("Merge Contacts…"));
    connect(action, &QAction::triggered, this, &MergeContactsPluginInterface::slotActivated);
    PimCommon::ActionType type(action, PimCommon::ActionType::Tools);
    addActionType(type);
}

void MergeContactsPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void MergeContactsPluginInterface::setCurrentItems(const Akonadi::Item::List &items)
{
    Akonadi::Item::List onlyContactList;
    for (const Akonadi::Item &item : items) {
        if (item.isValid() && item.hasPayload<KContacts::Addressee>()) {
            onlyContactList.append(item);
        }
    }

    mListItems = std::move(onlyContactList);
}

PimCommon::GenericPluginInterface::RequireTypes MergeContactsPluginInterface::requiresFeatures() const
{
    return PimCommon::GenericPluginInterface::CurrentItems;
}

void MergeContactsPluginInterface::exec()
{
    KABMergeContacts::MergeContactsDialog dlg(parentWidget());
    dlg.setContacts(mListItems);
    dlg.exec();
}

#include "moc_mergecontactsplugininterface.cpp"
