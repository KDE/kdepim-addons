/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingsgeneralwidget.h"
#include <MailCommon/CollectionGeneralWidget>
#include <QVBoxLayout>

FolderConfigureSettingsGeneralWidget::FolderConfigureSettingsGeneralWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mCollectionGeneralWidget = new MailCommon::CollectionGeneralWidget(this);
    mCollectionGeneralWidget->setObjectName(QStringLiteral("mCollectionGeneralWidget"));
    mainLayout->addWidget(mCollectionGeneralWidget);
    mainLayout->addStretch();
}

FolderConfigureSettingsGeneralWidget::~FolderConfigureSettingsGeneralWidget()
{
}

void FolderConfigureSettingsGeneralWidget::save()
{
}
