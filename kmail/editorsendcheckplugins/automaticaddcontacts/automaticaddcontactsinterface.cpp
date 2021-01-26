/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactsinterface.h"
#include "automaticaddcontactsjob.h"
#include <KConfigGroup>
#include <KIdentityManagement/Identity>
#include <KIdentityManagement/IdentityManager>
#include <KSharedConfig>

AutomaticAddContactsInterface::AutomaticAddContactsInterface(QObject *parent)
    : MessageComposer::PluginEditorCheckBeforeSendInterface(parent)
{
}

AutomaticAddContactsInterface::~AutomaticAddContactsInterface()
{
}

bool AutomaticAddContactsInterface::exec(const MessageComposer::PluginEditorCheckBeforeSendParams &params)
{
    AutomaticAddContactsSettings setting = mHashSettings.value(params.identity());
    if (setting.mEnabled) {
        if (setting.mContactCollection.isValid()) {
            QStringList lst;
            if (!params.ccAddresses().trimmed().isEmpty()) {
                lst << params.ccAddresses();
            }
            if (!params.bccAddresses().trimmed().isEmpty()) {
                lst << params.bccAddresses();
            }
            if (!params.toAddresses().trimmed().isEmpty()) {
                lst << params.toAddresses();
            }
            if (!lst.isEmpty()) {
                // Don't delete it, it's autodelete
                auto *job = new AutomaticAddContactsJob;
                job->setCollection(setting.mContactCollection);
                job->setEmails(lst);
                job->start();
            }
        }
    }
    return true;
}

void AutomaticAddContactsInterface::reloadConfig()
{
    mHashSettings.clear();

    KIdentityManagement::IdentityManager *im = KIdentityManagement::IdentityManager::self();
    KIdentityManagement::IdentityManager::ConstIterator end = im->end();
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    for (KIdentityManagement::IdentityManager::ConstIterator it = im->begin(); it != end; ++it) {
        const uint identity = (*it).uoid();
        KConfigGroup identityGroup = config->group(QStringLiteral("Automatic Add Contacts %1").arg(identity));
        AutomaticAddContactsSettings settings;
        settings.mEnabled = identityGroup.readEntry("Enabled", false);
        settings.mContactCollection = Akonadi::Collection(identityGroup.readEntry("Collection", -1));
        mHashSettings.insert(identity, settings);
    }
}
