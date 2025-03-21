/*
   SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingsexperywidget.h"

#include <MailCommon/CollectionExpiryWidget>

FolderConfigureSettingsExperyWidget::FolderConfigureSettingsExperyWidget(QWidget *parent)
    : FolderConfigureSettingsPageBase(parent)
    , mCollectionExpiryWidget(new MailCommon::CollectionExpiryWidget(this))
{
    mCollectionExpiryWidget->setObjectName(QLatin1StringView("mCollectionExpiryWidget"));
    mCollectionExpiryWidget->hideExpireNowButton();
    addMainWidget(mCollectionExpiryWidget);
}

FolderConfigureSettingsExperyWidget::~FolderConfigureSettingsExperyWidget() = default;

void FolderConfigureSettingsExperyWidget::save(Akonadi::Collection &col)
{
    if (MailCommon::CollectionExpiryWidget::canHandle(col)) {
        const MailCommon::CollectionExpirySettings settings = mCollectionExpiryWidget->settings();
        if (wasModified()) {
            mCollectionExpiryWidget->save(settings, col, true, false);
        }
    }
}

#include "moc_folderconfiguresettingsexperywidget.cpp"
