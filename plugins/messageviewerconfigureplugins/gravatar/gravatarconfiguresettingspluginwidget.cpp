/*
   Copyright (C) 2018-2019 Montel Laurent <montel@kde.org>

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

#include "gravatarconfiguresettingspluginwidget.h"
#include <QVBoxLayout>
#include <Gravatar/GravatarConfigWidget>

GravatarConfigureSettingsPluginWidget::GravatarConfigureSettingsPluginWidget(QWidget *parent)
    : MessageViewer::MessageViewerConfigureSettingsPluginWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mGravatarConfigWidget = new Gravatar::GravatarConfigWidget(this);
    mGravatarConfigWidget->setObjectName(QStringLiteral("gravatarconfigwidget"));
    mainLayout->addWidget(mGravatarConfigWidget);
}

GravatarConfigureSettingsPluginWidget::~GravatarConfigureSettingsPluginWidget()
{
}

void GravatarConfigureSettingsPluginWidget::loadSettings()
{
    mGravatarConfigWidget->doLoadFromGlobalSettings();
}

void GravatarConfigureSettingsPluginWidget::saveSettings()
{
    mGravatarConfigWidget->save();
}

void GravatarConfigureSettingsPluginWidget::resetSettings()
{
    mGravatarConfigWidget->doResetToDefaultsOther();
}
