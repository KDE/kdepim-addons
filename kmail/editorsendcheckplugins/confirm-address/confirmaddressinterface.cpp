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

#include "confirmaddressinterface.h"
#include "confirmaddressconfigurewidget.h"
#include "confirmaddressdialog.h"

#include <QPointer>
#include <KConfigGroup>
#include <KSharedConfig>

ConfirmAddressInterface::ConfirmAddressInterface(QObject *parent)
    : MessageComposer::PluginEditorCheckBeforeSendInterface(parent),
      mEnabled(false)
{
    reloadConfig();
}

ConfirmAddressInterface::~ConfirmAddressInterface()
{

}

bool ConfirmAddressInterface::exec(const MessageComposer::PluginEditorCheckBeforeSendParams &params)
{
    if (mEnabled) {
        QPointer<ConfirmAddressDialog> dlg = new ConfirmAddressDialog(parentWidget());
        //TODO use params
        if (dlg->exec()) {
            return true;
        } else {
            return false;
        }
    } else {
        return true;
    }
}

void ConfirmAddressInterface::reloadConfig()
{
    //TODO use identity ?
    KConfigGroup grp(KSharedConfig::openConfig(), "Confirm Address");
    mEnabled = grp.readEntry("Enabled", false);
    mDomains = grp.readEntry("Domains", QStringList());
    mWhiteLists = grp.readEntry("Emails", QStringList());
}
