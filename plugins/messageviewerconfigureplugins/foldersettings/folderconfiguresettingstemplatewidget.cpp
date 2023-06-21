/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingstemplatewidget.h"
#include <MailCommon/CollectionTemplatesWidget>

FolderConfigureSettingsTemplateWidget::FolderConfigureSettingsTemplateWidget(QWidget *parent)
    : FolderConfigureSettingsPageBase(parent)
    , mCollectionTemplateWidget(new MailCommon::CollectionTemplatesWidget(this))
{
    mCollectionTemplateWidget->setObjectName(QStringLiteral("mCollectionTemplateWidget"));
    addMainWidget(mCollectionTemplateWidget);
}

FolderConfigureSettingsTemplateWidget::~FolderConfigureSettingsTemplateWidget() = default;

void FolderConfigureSettingsTemplateWidget::save(Akonadi::Collection &col)
{
    if (wasModified()) {
        mCollectionTemplateWidget->save(col);
    }
}

#include "moc_folderconfiguresettingstemplatewidget.cpp"
