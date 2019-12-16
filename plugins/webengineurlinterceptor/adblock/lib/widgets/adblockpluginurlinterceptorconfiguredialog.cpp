/*
   Copyright (C) 2016-2019 Montel Laurent <montel@kde.org>

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

#include "adblockpluginurlinterceptorconfiguredialog.h"
#include "adblockautomaticruleslistwidget.h"
#include "adblockpluginurlinterceptorconfigurewidget.h"

#include <KLocalizedString>
#include <QWidget>

using namespace AdBlock;

AdblockPluginUrlInterceptorConfigureDialog::AdblockPluginUrlInterceptorConfigureDialog(QWidget *parent)
    : PimCommon::ConfigurePluginDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure AdBlock Plugin"));
    initLayout();
}

AdblockPluginUrlInterceptorConfigureDialog::~AdblockPluginUrlInterceptorConfigureDialog()
{
}

QWidget *AdblockPluginUrlInterceptorConfigureDialog::createLayout()
{
    mAdblockConfigureWidget = new AdblockPluginUrlInterceptorConfigureWidget(this);
    return mAdblockConfigureWidget;
}

void AdblockPluginUrlInterceptorConfigureDialog::save()
{
    mAdblockConfigureWidget->saveSettings();
}

void AdblockPluginUrlInterceptorConfigureDialog::load()
{
    mAdblockConfigureWidget->loadSettings();
}

void AdBlock::AdblockPluginUrlInterceptorConfigureDialog::reset()
{
    mAdblockConfigureWidget->resetSettings();
}

void AdBlock::AdblockPluginUrlInterceptorConfigureDialog::help()
{
    //TODO we can use in akregator too. We need a specific doc.
    showHelp(QStringLiteral("kmail2"), mAdblockConfigureWidget->helpAnchor());
}
