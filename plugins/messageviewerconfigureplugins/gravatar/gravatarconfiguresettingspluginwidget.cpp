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
#include <Gravatar/GravatarConfigWidget>
#include <Gravatar/GravatarConfigureSettingsWidget>
#include <Gravatar/GravatarCache>
#include <PimCommon/ConfigureImmutableWidgetUtils>

#include <KLocalizedString>

#include <gravatar/gravatarsettings.h>

#include <QCheckBox>
#include <QVBoxLayout>

using namespace PimCommon::ConfigureImmutableWidgetUtils;
GravatarConfigureSettingsPluginWidget::GravatarConfigureSettingsPluginWidget(QWidget *parent)
    : MessageViewer::MessageViewerConfigureSettingsPluginWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mEnableGravatarSupport = new QCheckBox(i18n("Enable Gravatar Support"));
    mEnableGravatarSupport->setObjectName(QStringLiteral("gravatarcheckbox"));
    mEnableGravatarSupport->setChecked(false);
    mainLayout->addWidget(mEnableGravatarSupport);

    mGravatarConfigWidget = new Gravatar::GravatarConfigureSettingsWidget(this);
    mGravatarConfigWidget->setObjectName(QStringLiteral("gravatarconfigwidget"));
    mainLayout->addWidget(mGravatarConfigWidget);
    connect(mEnableGravatarSupport, &QCheckBox::clicked, mGravatarConfigWidget, &Gravatar::GravatarConfigureSettingsWidget::setEnabled);
}

GravatarConfigureSettingsPluginWidget::~GravatarConfigureSettingsPluginWidget()
{
}

void GravatarConfigureSettingsPluginWidget::loadSettings()
{
    loadWidget(mEnableGravatarSupport, Gravatar::GravatarSettings::self()->gravatarSupportEnabledItem());
    mGravatarConfigWidget->load();
}

void GravatarConfigureSettingsPluginWidget::saveSettings()
{
    saveCheckBox(mEnableGravatarSupport, Gravatar::GravatarSettings::self()->gravatarSupportEnabledItem());
    if (!mEnableGravatarSupport->isChecked()) {
        Gravatar::GravatarCache::self()->clearAllCache();
    }
    mGravatarConfigWidget->save();
}

void GravatarConfigureSettingsPluginWidget::resetSettings()
{
    const bool bUseDefaults = Gravatar::GravatarSettings::self()->useDefaults(true);
    loadSettings();
    Gravatar::GravatarSettings::self()->useDefaults(bUseDefaults);
    mGravatarConfigWidget->slotRestoreDefault();
}
