/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimgeneralwidget.h"
#include <MessageViewer/MessageViewerSettings>
#include <MessageViewer/DKIMManager>
#include <KLocalizedString>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <PimCommon/ConfigureImmutableWidgetUtils>
using namespace PimCommon::ConfigureImmutableWidgetUtils;
DKIMGeneralWidget::DKIMGeneralWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mEnableDkimSupport = new QCheckBox(i18n("Enable DKIM Support"));
    mEnableDkimSupport->setObjectName(QStringLiteral("enableDkimSupport"));
    mEnableDkimSupport->setChecked(false);
    mainLayout->addWidget(mEnableDkimSupport);

    mSaveResult = new QCheckBox(i18n("Save DKIM Result"));
    mSaveResult->setObjectName(QStringLiteral("mSaveResult"));
    mSaveResult->setChecked(false);
    mainLayout->addWidget(mSaveResult);

    QHBoxLayout *saveKeyLayout = new QHBoxLayout;
    saveKeyLayout->setContentsMargins({});
    mainLayout->addLayout(saveKeyLayout);
    QLabel *saveKeyLabel = new QLabel(i18n("Save Record Key:"), this);
    saveKeyLabel->setObjectName(QStringLiteral("saveKeyLabel"));
    saveKeyLayout->addWidget(saveKeyLabel);

    mSaveKey = new QComboBox(this);
    mSaveKey->setObjectName(QStringLiteral("mSaveKey"));
    mSaveKey->addItems({i18n("Nothing"), i18n("Save"), i18n("Save and Compare")});
    saveKeyLayout->addWidget(mSaveKey);
    saveKeyLayout->addStretch(1);

    mUseOnlyAuthenticationResult = new QCheckBox(i18n("Replace DKIM result by Authentication-Result header value"));
    mUseOnlyAuthenticationResult->setObjectName(QStringLiteral("mUseOnlyAuthenticationResult"));
    mUseOnlyAuthenticationResult->setChecked(false);
    mainLayout->addWidget(mUseOnlyAuthenticationResult);

    mainLayout->addStretch(1);
}

DKIMGeneralWidget::~DKIMGeneralWidget()
{
}

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
