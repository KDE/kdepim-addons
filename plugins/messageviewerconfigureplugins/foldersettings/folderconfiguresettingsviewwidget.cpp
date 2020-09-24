/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingsviewwidget.h"
#include <MailCommon/CollectionViewWidget>
#include <QVBoxLayout>

FolderConfigureSettingsViewWidget::FolderConfigureSettingsViewWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mCollectionViewWidget = new MailCommon::CollectionViewWidget(this);
    mCollectionViewWidget->setObjectName(QStringLiteral("mCollectionTemplateWidget"));
    mainLayout->addWidget(mCollectionViewWidget);
}

FolderConfigureSettingsViewWidget::~FolderConfigureSettingsViewWidget()
{
}

void FolderConfigureSettingsViewWidget::save(Akonadi::Collection &col)
{
    mCollectionViewWidget->save(col);
}
