/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimgeneralwidget.h"
#include <KLocalizedString>
#include <MessageViewer/DKIMManager>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

DKIMGeneralWidget::DKIMGeneralWidget(QWidget *parent)
    : QWidget(parent)
    , mEnableDkimSupport(new QCheckBox(i18nc("@option:check", "Enable DKIM Support"), this))
    , mSaveResult(new QCheckBox(i18nc("@option:check", "Save DKIM Result"), this))
    , mSaveKey(new QComboBox(this))
    , mUseOnlyAuthenticationResult(new QCheckBox(i18nc("@option:check", "Replace DKIM result by Authentication-Result header value"), this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);

    mEnableDkimSupport->setObjectName("kcfg_EnabledDkim"_L1);
    mEnableDkimSupport->setChecked(false);
    mainLayout->addWidget(mEnableDkimSupport);

    mSaveResult->setObjectName("kcfg_SaveDkimResult"_L1);
    mSaveResult->setChecked(false);
    mainLayout->addWidget(mSaveResult);

    auto saveKeyLayout = new QHBoxLayout;
    saveKeyLayout->setContentsMargins({});
    mainLayout->addLayout(saveKeyLayout);
    auto saveKeyLabel = new QLabel(i18nc("@label:textbox", "Save Record Key:"), this);
    saveKeyLabel->setObjectName("saveKeyLabel"_L1);
    saveKeyLayout->addWidget(saveKeyLabel);

    mSaveKey->setObjectName("kcfg_SaveKey"_L1);
    mSaveKey->addItems({i18n("Nothing"), i18n("Save"), i18n("Save and Compare")});
    saveKeyLayout->addWidget(mSaveKey);
    saveKeyLayout->addStretch(1);

    mUseOnlyAuthenticationResult->setObjectName("kcfg_UseOnlyAuthenticationResults"_L1);
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

#include "moc_dkimgeneralwidget.cpp"
