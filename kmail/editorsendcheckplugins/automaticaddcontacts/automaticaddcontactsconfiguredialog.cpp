/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactsconfiguredialog.h"
using namespace Qt::Literals::StringLiterals;

#include "automaticaddcontactsconfigurewidget.h"
#include <KLocalizedString>

AutomaticAddContactsConfigureDialog::AutomaticAddContactsConfigureDialog(QWidget *parent)
    : PimCommon::ConfigurePluginDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure \"Automatic Add Contacts\" Plugin"));
    initLayout();
}

AutomaticAddContactsConfigureDialog::~AutomaticAddContactsConfigureDialog() = default;

QWidget *AutomaticAddContactsConfigureDialog::createLayout()
{
    mConfigureWidget = new AutomaticAddContactsConfigureWidget(this);
    return mConfigureWidget;
}

void AutomaticAddContactsConfigureDialog::save()
{
    mConfigureWidget->saveSettings();
}

void AutomaticAddContactsConfigureDialog::load()
{
    mConfigureWidget->loadSettings();
}

void AutomaticAddContactsConfigureDialog::reset()
{
    mConfigureWidget->resetSettings();
}

void AutomaticAddContactsConfigureDialog::help()
{
    showHelp(u"kmail2"_s, mConfigureWidget->helpAnchor());
}

#include "moc_automaticaddcontactsconfiguredialog.cpp"
