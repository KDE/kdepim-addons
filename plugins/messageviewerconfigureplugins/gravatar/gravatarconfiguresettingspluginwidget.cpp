/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "gravatarconfiguresettingspluginwidget.h"
#include <Gravatar/GravatarCache>
#include <Gravatar/GravatarConfigureSettingsWidget>
#include <PimCommon/ConfigureImmutableWidgetUtils>

#include <KLocalizedString>

#include <gravatar/gravatarsettings.h>

#include <QCheckBox>
#include <QVBoxLayout>

using namespace PimCommon::ConfigureImmutableWidgetUtils;
GravatarConfigureSettingsPluginWidget::GravatarConfigureSettingsPluginWidget(QWidget *parent)
    : MessageViewer::MessageViewerConfigureSettingsPluginWidget(parent)
    , mGravatarConfigWidget(new Gravatar::GravatarConfigureSettingsWidget(this))
    , mEnableGravatarSupport(new QCheckBox(i18n("Enable Gravatar Support"), this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));
    mainLayout->setContentsMargins({});

    mEnableGravatarSupport->setObjectName(QLatin1StringView("gravatarcheckbox"));
    mEnableGravatarSupport->setChecked(false);
    mainLayout->addWidget(mEnableGravatarSupport);

    mGravatarConfigWidget->setObjectName(QLatin1StringView("gravatarconfigwidget"));
    mainLayout->addWidget(mGravatarConfigWidget);
    connect(mEnableGravatarSupport, &QCheckBox::clicked, mGravatarConfigWidget, &Gravatar::GravatarConfigureSettingsWidget::setEnabled);
}

GravatarConfigureSettingsPluginWidget::~GravatarConfigureSettingsPluginWidget() = default;

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

#include "moc_gravatarconfiguresettingspluginwidget.cpp"
