/*
   SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingsgeneralwidget.h"
#include <MailCommon/CollectionGeneralWidget>
#include <QHBoxLayout>

FolderConfigureSettingsGeneralWidget::FolderConfigureSettingsGeneralWidget(QWidget *parent)
    : FolderConfigureSettingsPageBase(parent)
    , mCollectionGeneralWidget(new MailCommon::CollectionGeneralWidget(this))
{
    auto mainWidget = new QWidget(this);
    auto mainLayout = new QHBoxLayout(mainWidget);
    mCollectionGeneralWidget->setObjectName(QStringLiteral("mCollectionGeneralWidget"));
    mainLayout->addWidget(mCollectionGeneralWidget);
    addMainWidget(mainWidget);
    mMainLayout->addStretch();
}

FolderConfigureSettingsGeneralWidget::~FolderConfigureSettingsGeneralWidget()
{
}

void FolderConfigureSettingsGeneralWidget::save(Akonadi::Collection &col)
{
    if (wasModified()) {
        mCollectionGeneralWidget->save(col);
    }
}
