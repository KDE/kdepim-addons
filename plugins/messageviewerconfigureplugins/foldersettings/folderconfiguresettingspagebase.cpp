/*
   SPDX-FileCopyrightText: 2020-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingspagebase.h"

#include <KLocalizedString>

#include <QGroupBox>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

FolderConfigureSettingsPageBase::FolderConfigureSettingsPageBase(QWidget *parent)
    : QWidget(parent)
    , mMainLayout(new QVBoxLayout)
    , mGroupBox(new QGroupBox(i18n("Modify"), this))
{
    auto topLayout = new QVBoxLayout(this);
    topLayout->setObjectName("topLayout"_L1);

    mMainLayout->setObjectName("mMainLayout"_L1);

    mGroupBox->setObjectName("mGroupBox"_L1);
    mGroupBox->setCheckable(true);
    mGroupBox->setChecked(false);

    mGroupBox->setLayout(mMainLayout);
    topLayout->addWidget(mGroupBox);
    connect(mGroupBox, &QGroupBox::clicked, this, &FolderConfigureSettingsPageBase::slotModifyClicked);
}

FolderConfigureSettingsPageBase::~FolderConfigureSettingsPageBase() = default;

void FolderConfigureSettingsPageBase::slotModifyClicked(bool clicked)
{
    mMainWidget->setEnabled(clicked);
}

bool FolderConfigureSettingsPageBase::wasModified() const
{
    return mGroupBox->isChecked();
}

void FolderConfigureSettingsPageBase::addMainWidget(QWidget *widget)
{
    mMainWidget = widget;
    mMainLayout->addWidget(mMainWidget);
    mMainWidget->setEnabled(false); // Disable it directly
}

#include "moc_folderconfiguresettingspagebase.cpp"
