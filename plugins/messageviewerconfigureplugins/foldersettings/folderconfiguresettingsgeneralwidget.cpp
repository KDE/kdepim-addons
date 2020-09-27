/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingsgeneralwidget.h"
#include <MailCommon/CollectionGeneralWidget>
#include <QVBoxLayout>

FolderConfigureSettingsGeneralWidget::FolderConfigureSettingsGeneralWidget(QWidget *parent)
    : FolderConfigureSettingsPageBase(parent)
{
    mCollectionGeneralWidget = new MailCommon::CollectionGeneralWidget(this);
    mCollectionGeneralWidget->setObjectName(QStringLiteral("mCollectionGeneralWidget"));
    addMainWidget(mCollectionGeneralWidget);
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
