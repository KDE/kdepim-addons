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

#include "automaticaddcontactsinterface.h"
#include "automaticaddcontactsjob.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <KIdentityManagement/IdentityManager>
#include <KIdentityManagement/Identity>

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
                //Don't delete it, it's autodelete
                AutomaticAddContactsJob *job = new AutomaticAddContactsJob;
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
