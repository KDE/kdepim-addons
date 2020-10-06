/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "gravatarconfiguresettingspluginwidget.h"
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
    mainLayout->setContentsMargins({});

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
