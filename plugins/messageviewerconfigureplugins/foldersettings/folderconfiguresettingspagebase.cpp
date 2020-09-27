/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingspagebase.h"

#include <KLocalizedString>

#include <QCheckBox>
#include <QVBoxLayout>

FolderConfigureSettingsPageBase::FolderConfigureSettingsPageBase(QWidget *parent)
    : QWidget(parent)
    , mMainLayout(new QVBoxLayout(this))
{
    mMainLayout->setObjectName(QStringLiteral("mMainLayout"));
    mModifyCheckBox = new QCheckBox(i18n("Modify Settings"), this);
    mModifyCheckBox->setObjectName(QStringLiteral("mModifiedCheckBox"));
    mModifyCheckBox->setChecked(false);
    mMainLayout->addWidget(mModifyCheckBox);
    connect(mModifyCheckBox, &QCheckBox::clicked, this, &FolderConfigureSettingsPageBase::slotModifyClicked);
}

FolderConfigureSettingsPageBase::~FolderConfigureSettingsPageBase()
{

}

void FolderConfigureSettingsPageBase::slotModifyClicked(bool clicked)
{
    mMainWidget->setEnabled(clicked);
}

bool FolderConfigureSettingsPageBase::wasModified() const
{
    return mModifyCheckBox->isChecked();
}

void FolderConfigureSettingsPageBase::addMainWidget(QWidget *widget)
{
    mMainWidget = widget;
    mMainLayout->addWidget(mMainWidget);
    mMainWidget->setEnabled(false); //Disable it directly
}
