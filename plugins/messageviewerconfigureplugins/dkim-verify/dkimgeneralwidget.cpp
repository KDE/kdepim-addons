/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimgeneralwidget.h"
#include <KLocalizedString>
#include <MessageViewer/DKIMManager>
#include <MessageViewer/MessageViewerSettings>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>

DKIMGeneralWidget::DKIMGeneralWidget(QWidget *parent)
    : QWidget(parent)
    , mEnableDkimSupport(new QCheckBox(i18n("Enable DKIM Support"), this))
    , mSaveResult(new QCheckBox(i18n("Save DKIM Result"), this))
    , mSaveKey(new QComboBox(this))
    , mUseOnlyAuthenticationResult(new QCheckBox(i18n("Replace DKIM result by Authentication-Result header value"), this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mEnableDkimSupport->setObjectName(QStringLiteral("kcfg_EnabledDkim"));
    mEnableDkimSupport->setChecked(false);
    mainLayout->addWidget(mEnableDkimSupport);

    mSaveResult->setObjectName(QStringLiteral("kcfg_SaveDkimResult"));
    mSaveResult->setChecked(false);
    mainLayout->addWidget(mSaveResult);

    auto saveKeyLayout = new QHBoxLayout;
    saveKeyLayout->setContentsMargins({});
    mainLayout->addLayout(saveKeyLayout);
    auto saveKeyLabel = new QLabel(i18n("Save Record Key:"), this);
    saveKeyLabel->setObjectName(QStringLiteral("saveKeyLabel"));
    saveKeyLayout->addWidget(saveKeyLabel);

    mSaveKey->setObjectName(QStringLiteral("kcfg_SaveKey"));
    mSaveKey->addItems({i18n("Nothing"), i18n("Save"), i18n("Save and Compare")});
    saveKeyLayout->addWidget(mSaveKey);
    saveKeyLayout->addStretch(1);

    mUseOnlyAuthenticationResult->setObjectName(QStringLiteral("kcfg_UseOnlyAuthenticationResults"));
    mUseOnlyAuthenticationResult->setChecked(false);
    mainLayout->addWidget(mUseOnlyAuthenticationResult);

    mainLayout->addStretch(1);
}

DKIMGeneralWidget::~DKIMGeneralWidget() = default;

void DKIMGeneralWidget::saveSettings()
{
    if (!mEnableDkimSupport->isChecked()) {
        MessageViewer::DKIMManager::self()->clearInfoWidget();
    }
}
