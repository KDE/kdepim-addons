/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingspagebase.h"

#include <KLocalizedString>

#include <QGroupBox>
#include <QVBoxLayout>

FolderConfigureSettingsPageBase::FolderConfigureSettingsPageBase(QWidget *parent)
    : QWidget(parent)
    , mMainLayout(new QVBoxLayout)
    , mGroupBox(new QGroupBox(i18n("Modify"), this))
{
    auto topLayout = new QVBoxLayout(this);
    topLayout->setObjectName(QStringLiteral("topLayout"));

    mMainLayout->setObjectName(QStringLiteral("mMainLayout"));

    mGroupBox->setObjectName(QStringLiteral("mGroupBox"));
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
