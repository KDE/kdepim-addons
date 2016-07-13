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

#include "automaticaddcontactsinterface.h"
#include "automaticaddcontactsjob.h"
#include <KConfigGroup>
#include <KSharedConfig>

AutomaticAddContactsInterface::AutomaticAddContactsInterface(QObject *parent)
    : MessageComposer::PluginEditorCheckBeforeSendInterface(parent)
{
    reloadConfig();
}

AutomaticAddContactsInterface::~AutomaticAddContactsInterface()
{

}

bool AutomaticAddContactsInterface::exec(const MessageComposer::PluginEditorCheckBeforeSendParams &params)
{
    if (mEnabled) {
        if (mContactCollection.isValid()) {
            const QStringList lst{ params.bccAddresses(), params.toAddresses(), params.ccAddresses() };
            if (!lst.isEmpty()) {
                //Don't delete it, it's autodelete
                AutomaticAddContactsJob *job = new AutomaticAddContactsJob;
                job->setCollection(mContactCollection);
                job->setEmails(lst);
                job->start();
            }
        }
    }
    return true;
}

void AutomaticAddContactsInterface::reloadConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Automatic Add Contacts");
    mEnabled = grp.readEntry("Enabled", false);
    mContactCollection = Akonadi::Collection(grp.readEntry("Collection", -1));
}
