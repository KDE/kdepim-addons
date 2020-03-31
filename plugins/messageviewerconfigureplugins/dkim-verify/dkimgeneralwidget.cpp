/*
   Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mEnableDkimSupport = new QCheckBox(i18n("Enable DKIM Support"));
    mEnableDkimSupport->setObjectName(QStringLiteral("enableDkimSupport"));
    mEnableDkimSupport->setChecked(false);
    mainLayout->addWidget(mEnableDkimSupport);

    mSaveResult = new QCheckBox(i18n("Save DKIM Result"));
    mSaveResult->setObjectName(QStringLiteral("mSaveResult"));
    mSaveResult->setChecked(false);
    mainLayout->addWidget(mSaveResult);

    QHBoxLayout *saveKeyLayout = new QHBoxLayout;
    saveKeyLayout->setContentsMargins(0, 0, 0, 0);
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
