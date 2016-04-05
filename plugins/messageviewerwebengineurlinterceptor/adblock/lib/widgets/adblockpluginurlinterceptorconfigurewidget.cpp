/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "adblockpluginurlinterceptorconfigurewidget.h"
#include <MessageViewer/AdBlockSettingWidget>
#include <KLocalizedString>
#include <QHBoxLayout>

using namespace AdBlock;

AdblockPluginUrlInterceptorConfigureWidget::AdblockPluginUrlInterceptorConfigureWidget(QWidget *parent)
    : MessageViewer::NetworkPluginUrlInterceptorConfigureWidget(parent)
{
    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->setMargin(0);
    mConfigureWidget = new MessageViewer::AdBlockSettingWidget(this);
    mConfigureWidget->setObjectName(QStringLiteral("configurewidget"));
    hbox->addWidget(mConfigureWidget);
    connect(mConfigureWidget, &MessageViewer::AdBlockSettingWidget::settingsChanged, this, &AdblockPluginUrlInterceptorConfigureWidget::configureChanged);
}

AdblockPluginUrlInterceptorConfigureWidget::~AdblockPluginUrlInterceptorConfigureWidget()
{

}

void AdblockPluginUrlInterceptorConfigureWidget::loadSettings()
{
    mConfigureWidget->doLoadFromGlobalSettings();
}

void AdblockPluginUrlInterceptorConfigureWidget::saveSettings()
{
    mConfigureWidget->save();
    Q_EMIT configureChanged();
}

void AdblockPluginUrlInterceptorConfigureWidget::resetSettings()
{
    mConfigureWidget->doResetToDefaultsOther();
}
