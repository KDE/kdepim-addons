/*
   Copyright (C) 2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "expireaccounttrashfolderconfigwidget.h"
#include "libexpireaccounttrashfolderconfig_debug.h"
#include <MailCommon/CollectionExpiryWidget>
#include <AkonadiCore/AgentManager>
#include <akonadi/kmime/specialmailcollections.h>
#include <QVBoxLayout>

ExpireAccountTrashFolderConfigWidget::ExpireAccountTrashFolderConfigWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);


     mCollectionExpiryWidget = new MailCommon::CollectionExpiryWidget(this);
     mCollectionExpiryWidget->setObjectName(QStringLiteral("mCollectionExpiryWidget"));
     connect(mCollectionExpiryWidget, &MailCommon::CollectionExpiryWidget::saveAndExpireRequested, this, &ExpireAccountTrashFolderConfigWidget::slotSaveAndExpireRequested);
     mainLayout->addWidget(mCollectionExpiryWidget);
}

ExpireAccountTrashFolderConfigWidget::~ExpireAccountTrashFolderConfigWidget()
{

}

void ExpireAccountTrashFolderConfigWidget::save(bool saveSettings, bool expireNow)
{
    const MailCommon::CollectionExpirySettings settings = mCollectionExpiryWidget->settings();
    const Akonadi::AgentInstance::List agents = Akonadi::AgentManager::self()->instances();
    QList<Akonadi::Collection::Id> mListCollection;
    for (const Akonadi::AgentInstance &agent : agents) {
        Akonadi::Collection trashCol = Akonadi::SpecialMailCollections::self()->collection(Akonadi::SpecialMailCollections::Trash, agent);
        const auto trashColId = trashCol.id();
        //qCDebug(LIBEXPIREACCOUNTTRASHFOLDERCONFIG_PLUGIN_LOG) << "Trash collection found " << trashCol;
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
