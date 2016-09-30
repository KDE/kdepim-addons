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

#include "confirmaddressconfiguredialog.h"
#include "confirmaddressconfigurewidget.h"
#include <KIdentityManagement/IdentityManager>
#include <KLocalizedString>

ConfirmAddressConfigureDialog::ConfirmAddressConfigureDialog(QWidget *parent)
    : PimCommon::ConfigurePluginDialog(parent),
      mConfigureWidget(Q_NULLPTR)
{
    setWindowTitle(i18n("Configure \"Confirm Email Address\" Before Send Plugin"));
    initLayout();
}

ConfirmAddressConfigureDialog::~ConfirmAddressConfigureDialog()
{

}

QWidget *ConfirmAddressConfigureDialog::createLayout()
{
    mConfigureWidget = new ConfirmAddressConfigureWidget(KIdentityManagement::IdentityManager::self(), this);
    return mConfigureWidget;
}

void ConfirmAddressConfigureDialog::save()
{
    mConfigureWidget->saveSettings();
}

void ConfirmAddressConfigureDialog::load()
{
    mConfigureWidget->loadSettings();
}

void ConfirmAddressConfigureDialog::reset()
{
    mConfigureWidget->resetSettings();
}

void ConfirmAddressConfigureDialog::help()
{
    showHelp(QStringLiteral("kmail"), QString());
}
