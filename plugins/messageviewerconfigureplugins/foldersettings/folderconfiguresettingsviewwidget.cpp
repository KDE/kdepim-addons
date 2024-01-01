/*
   SPDX-FileCopyrightText: 2020-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingsviewwidget.h"
#include <MailCommon/CollectionViewWidget>
#include <QHBoxLayout>
FolderConfigureSettingsViewWidget::FolderConfigureSettingsViewWidget(QWidget *parent)
    : FolderConfigureSettingsPageBase(parent)
    , mCollectionViewWidget(new MailCommon::CollectionViewWidget(this))
{
    auto mainWidget = new QWidget(this);
    auto mainLayout = new QHBoxLayout(mainWidget);
    mCollectionViewWidget->setObjectName(QLatin1StringView("mCollectionTemplateWidget"));
    mainLayout->addWidget(mCollectionViewWidget);
    addMainWidget(mainWidget);
    mMainLayout->addStretch();
}

FolderConfigureSettingsViewWidget::~FolderConfigureSettingsViewWidget() = default;

void FolderConfigureSettingsViewWidget::save(Akonadi::Collection &col)
{
    if (wasModified()) {
        mCollectionViewWidget->save(col);
    }
}

#include "moc_folderconfiguresettingsviewwidget.cpp"
