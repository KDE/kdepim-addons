/*
   SPDX-FileCopyrightText: 2020-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingsexperywidget.h"

#include <MailCommon/CollectionExpiryWidget>
using namespace Qt::Literals::StringLiterals;

FolderConfigureSettingsExperyWidget::FolderConfigureSettingsExperyWidget(QWidget *parent)
    : FolderConfigureSettingsPageBase(parent)
    , mCollectionExpiryWidget(new MailCommon::CollectionExpiryWidget(this))
{
    mCollectionExpiryWidget->setObjectName("mCollectionExpiryWidget"_L1);
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
