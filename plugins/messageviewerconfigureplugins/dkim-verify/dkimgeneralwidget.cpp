/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimgeneralwidget.h"
#include <KLocalizedString>
#include <MessageViewer/DKIMManager>
#include <MessageViewer/MessageViewerSettings>
#include <PimCommon/ConfigureImmutableWidgetUtils>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
using namespace PimCommon::ConfigureImmutableWidgetUtils;
DKIMGeneralWidget::DKIMGeneralWidget(QWidget *parent)
    : QWidget(parent)
    , mEnableDkimSupport(new QCheckBox(i18n("Enable DKIM Support"), this))
    , mSaveResult(new QCheckBox(i18n("Save DKIM Result"), this))
    , mSaveKey(new QComboBox(this))
    , mUseOnlyAuthenticationResult(new QCheckBox(i18n("Replace DKIM result by Authentication-Result header value"), this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mEnableDkimSupport->setObjectName(QStringLiteral("enableDkimSupport"));
    mEnableDkimSupport->setChecked(false);
    mainLayout->addWidget(mEnableDkimSupport);

    mSaveResult->setObjectName(QStringLiteral("mSaveResult"));
    mSaveResult->setChecked(false);
    mainLayout->addWidget(mSaveResult);

    auto saveKeyLayout = new QHBoxLayout;
    saveKeyLayout->setContentsMargins({});
    mainLayout->addLayout(saveKeyLayout);
    auto saveKeyLabel = new QLabel(i18n("Save Record Key:"), this);
    saveKeyLabel->setObjectName(QStringLiteral("saveKeyLabel"));
    saveKeyLayout->addWidget(saveKeyLabel);

    mSaveKey->setObjectName(QStringLiteral("mSaveKey"));
    mSaveKey->addItems({i18n("Nothing"), i18n("Save"), i18n("Save and Compare")});
    saveKeyLayout->addWidget(mSaveKey);
    saveKeyLayout->addStretch(1);

    mUseOnlyAuthenticationResult->setObjectName(QStringLiteral("mUseOnlyAuthenticationResult"));
    mUseOnlyAuthenticationResult->setChecked(false);
    mainLayout->addWidget(mUseOnlyAuthenticationResult);

    mainLayout->addStretch(1);
}

DKIMGeneralWidget::~DKIMGeneralWidget() = default;

void DKIMGeneralWidget::loadSettings()
{
    loadWidget(mEnableDkimSupport, MessageViewer::MessageViewerSettings::self()->enabledDkimItem());
    loadWidget(mSaveResult, MessageViewer::MessageViewerSettings::self()->saveDkimResultItem());
    loadWidget(mSaveKey, MessageViewer::MessageViewerSettings::self()->saveKeyItem());
    loadWidget(mUseOnlyAuthenticationResult, MessageViewer::MessageViewerSettings::self()->useOnlyAuthenticationResultsItem());
}

void DKIMGeneralWidget::saveSettings()
{
    saveCheckBox(mEnableDkimSupport, MessageViewer::MessageViewerSettings::self()->enabledDkimItem());
    saveCheckBox(mSaveResult, MessageViewer::MessageViewerSettings::self()->saveDkimResultItem());
    saveComboBox(mSaveKey, MessageViewer::MessageViewerSettings::self()->saveKeyItem());
    if (!mEnableDkimSupport->isChecked()) {
        MessageViewer::DKIMManager::self()->clearInfoWidget();
    }
    loadWidget(mUseOnlyAuthenticationResult, MessageViewer::MessageViewerSettings::self()->useOnlyAuthenticationResultsItem());
}

void DKIMGeneralWidget::resetSettings()
{
    const bool bUseDefaults = MessageViewer::MessageViewerSettings::self()->useDefaults(true);
    loadSettings();
    MessageViewer::MessageViewerSettings::self()->useDefaults(bUseDefaults);
}
