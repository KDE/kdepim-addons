/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "expireaccounttrashfolderconfigwidget.h"
#include "libexpireaccounttrashfolderconfig_debug.h"
#include <Akonadi/AgentManager>
#include <Akonadi/SpecialMailCollections>
#include <MailCommon/CollectionExpiryWidget>
#include <QVBoxLayout>

ExpireAccountTrashFolderConfigWidget::ExpireAccountTrashFolderConfigWidget(QWidget *parent)
    : QWidget(parent)
    , mCollectionExpiryWidget(new MailCommon::CollectionExpiryWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mCollectionExpiryWidget->setObjectName(QStringLiteral("mCollectionExpiryWidget"));
    connect(mCollectionExpiryWidget,
            &MailCommon::CollectionExpiryWidget::saveAndExpireRequested,
            this,
            &ExpireAccountTrashFolderConfigWidget::slotSaveAndExpireRequested);
    mainLayout->addWidget(mCollectionExpiryWidget);
}

ExpireAccountTrashFolderConfigWidget::~ExpireAccountTrashFolderConfigWidget() = default;

void ExpireAccountTrashFolderConfigWidget::save(bool saveSettings, bool expireNow)
{
    const MailCommon::CollectionExpirySettings settings = mCollectionExpiryWidget->settings();
    const Akonadi::AgentInstance::List agents = Akonadi::AgentManager::self()->instances();
    QList<Akonadi::Collection::Id> mListCollection;
    for (const Akonadi::AgentInstance &agent : agents) {
        Akonadi::Collection trashCol = Akonadi::SpecialMailCollections::self()->collection(Akonadi::SpecialMailCollections::Trash, agent);
        const auto trashColId = trashCol.id();
        // qCDebug(LIBEXPIREACCOUNTTRASHFOLDERCONFIG_PLUGIN_LOG) << "Trash collection found " << trashCol;
        if (trashCol.isValid()) {
            qCDebug(LIBEXPIREACCOUNTTRASHFOLDERCONFIG_PLUGIN_LOG) << "Trash collection valid found " << trashCol;
            if (mListCollection.contains(trashColId)) {
                continue;
            }
            mListCollection.append(trashColId);
            mCollectionExpiryWidget->save(settings, trashCol, saveSettings, expireNow);
        }
    }
}

void ExpireAccountTrashFolderConfigWidget::save()
{
    save(true, false);
}

void ExpireAccountTrashFolderConfigWidget::slotSaveAndExpireRequested()
{
    save(true, true);
}

#include "moc_expireaccounttrashfolderconfigwidget.cpp"
