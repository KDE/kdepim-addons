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
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);

    mEnableDkimSupport->setObjectName("kcfg_EnabledDkim"_L1);
    mEnableDkimSupport->setChecked(false);
    mainLayout->addWidget(mEnableDkimSupport);

    auto saveResult = new QCheckBox(i18nc("@option:check", "Save DKIM Result"), this);
    saveResult->setObjectName("kcfg_SaveDkimResult"_L1);
    saveResult->setChecked(false);
    mainLayout->addWidget(saveResult);

    auto saveKeyLayout = new QHBoxLayout;
    saveKeyLayout->setContentsMargins({});
    mainLayout->addLayout(saveKeyLayout);
    auto saveKeyLabel = new QLabel(i18nc("@label:textbox", "Save Record Key:"), this);
    saveKeyLabel->setObjectName("saveKeyLabel"_L1);
    saveKeyLayout->addWidget(saveKeyLabel);

    auto saveKey = new QComboBox(this);
    saveKey->setObjectName("kcfg_SaveKey"_L1);
    saveKey->addItems({i18n("Nothing"), i18n("Save"), i18n("Save and Compare")});
    saveKeyLayout->addWidget(saveKey);
    saveKeyLayout->addStretch(1);

    auto useOnlyAuthenticationResult = new QCheckBox(i18nc("@option:check", "Replace DKIM result by Authentication-Result header value"), this);
    useOnlyAuthenticationResult->setObjectName("kcfg_UseOnlyAuthenticationResults"_L1);
    useOnlyAuthenticationResult->setChecked(false);
    mainLayout->addWidget(useOnlyAuthenticationResult);

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
