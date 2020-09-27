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
    mCollectionViewWidget = new MailCommon::CollectionViewWidget(this);
    mCollectionViewWidget->setObjectName(QStringLiteral("mCollectionTemplateWidget"));
    addMainWidget(mCollectionViewWidget);
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
