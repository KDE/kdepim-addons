/*
   Copyright (C) 2017 Montel Laurent <montel@kde.org>

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

#include "externalcomposerconfiguredialog.h"
#include "externalcomposerconfigurewidget.h"
#include <KIdentityManagement/IdentityManager>
#include <KLocalizedString>

ExternalComposerConfigureDialog::ExternalComposerConfigureDialog(QWidget *parent)
    : PimCommon::ConfigurePluginDialog(parent)
    , mConfigureWidget(nullptr)
{
    setWindowTitle(i18n("Configure \"Automatic Add Contacts\" Plugin"));
    initLayout();
}

ExternalComposerConfigureDialog::~ExternalComposerConfigureDialog()
{
}

QWidget *ExternalComposerConfigureDialog::createLayout()
{
    mConfigureWidget = new ExternalComposerConfigureWidget(this);
    return mConfigureWidget;
}

void ExternalComposerConfigureDialog::save()
{
    mConfigureWidget->saveSettings();
}

void ExternalComposerConfigureDialog::load()
{
    mConfigureWidget->loadSettings();
}

void ExternalComposerConfigureDialog::reset()
{
    mConfigureWidget->resetSettings();
}

void ExternalComposerConfigureDialog::help()
{
    showHelp(QStringLiteral("kmail2"), QString());
}
