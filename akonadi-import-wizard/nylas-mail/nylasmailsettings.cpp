/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "nylasmailsettings.h"
#include <ImportWizard/ImportWizardUtil>

#include <MailTransport/TransportManager>

#include <KIdentityManagement/kidentitymanagement/identity.h>
#include <KIdentityManagement/kidentitymanagement/signature.h>

NylasMailSettings::NylasMailSettings(const QString &filename)
{
}

NylasMailSettings::~NylasMailSettings()
{
}

void NylasMailSettings::importSettings()
{
    readImapAccount();
    readTransport();
    readIdentity();
    readGlobalSettings();
}

void NylasMailSettings::readImapAccount()
{
}

void NylasMailSettings::readTransport()
{
}

void NylasMailSettings::readIdentity()
{
}

void NylasMailSettings::readGlobalSettings()
{
    //TODO
}
