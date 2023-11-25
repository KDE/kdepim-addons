/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

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
    mCollectionGeneralWidget->setObjectName(QLatin1StringView("mCollectionGeneralWidget"));
    mainLayout->addWidget(mCollectionGeneralWidget);
    addMainWidget(mainWidget);
    mMainLayout->addStretch();
}

FolderConfigureSettingsGeneralWidget::~FolderConfigureSettingsGeneralWidget() = default;

void FolderConfigureSettingsGeneralWidget::save(Akonadi::Collection &col)
{
    if (wasModified()) {
        mCollectionGeneralWidget->save(col);
    }
}

#include "moc_folderconfiguresettingsgeneralwidget.cpp"
