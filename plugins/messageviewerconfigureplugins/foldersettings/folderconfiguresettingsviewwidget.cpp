/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingsviewwidget.h"
#include <MailCommon/CollectionViewWidget>
#include <QVBoxLayout>

FolderConfigureSettingsViewWidget::FolderConfigureSettingsViewWidget(QWidget *parent)
    : FolderConfigureSettingsPageBase(parent)
{
    QWidget *mainWidget = new QWidget(this);
    auto *mainLayout = new QHBoxLayout(mainWidget);
    mCollectionViewWidget = new MailCommon::CollectionViewWidget(this);
    mCollectionViewWidget->setObjectName(QStringLiteral("mCollectionTemplateWidget"));
    mainLayout->addWidget(mCollectionViewWidget);
    addMainWidget(mainWidget);
    mMainLayout->addStretch();
}

FolderConfigureSettingsViewWidget::~FolderConfigureSettingsViewWidget()
{
}

void FolderConfigureSettingsViewWidget::save(Akonadi::Collection &col)
{
    if (wasModified()) {
        mCollectionViewWidget->save(col);
    }
}
