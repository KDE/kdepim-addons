/*
    SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "searchpotentialduplicatecontactjob.h"
#include "kaddressbookmergelibprivate_debug.h"

#include <KContacts/Addressee>

using namespace KABMergeContacts;

SearchPotentialDuplicateContactJob::SearchPotentialDuplicateContactJob(const Akonadi::Item::List &list, QObject *parent)
    : QObject(parent)
    , mListItem(list)
{
}

SearchPotentialDuplicateContactJob::~SearchPotentialDuplicateContactJob() = default;

void SearchPotentialDuplicateContactJob::start()
{
    mListDuplicate.clear();
    Akonadi::Item::List result = mListItem;
    while (!result.isEmpty()) {
        result = checkList(result);
    }
    Q_EMIT finished(mListDuplicate);
    deleteLater();
}

QList<Akonadi::Item::List> SearchPotentialDuplicateContactJob::potentialDuplicateContacts() const
{
    return mListDuplicate;
}

Akonadi::Item::List SearchPotentialDuplicateContactJob::checkList(const Akonadi::Item::List &lstItem)
{
    Akonadi::Item::List notDuplicate;
    Akonadi::Item::List lst;
    if (!lstItem.isEmpty()) {
        const Akonadi::Item firstItem = lstItem.at(0);
        const int numberOfItems(lstItem.count());
        for (int j = 1; j < numberOfItems; ++j) {
            const Akonadi::Item nextItem = lstItem.at(j);
            if (isDuplicate(firstItem, nextItem)) {
                lst.append(nextItem);
            } else {
                notDuplicate.append(nextItem);
            }
        }
        if (!lst.isEmpty()) {
            lst.append(firstItem);
            mListDuplicate.append(lst);
        }
        qCDebug(KADDRESSBOOKMERGELIBPRIVATE_LOG) << " duplicate number " << lst.count();
    }
    return notDuplicate;
}

bool SearchPotentialDuplicateContactJob::isDuplicate(const Akonadi::Item &itemA, const Akonadi::Item &itemB)
{
    if (!itemA.hasPayload<KContacts::Addressee>() || !itemB.hasPayload<KContacts::Addressee>()) {
        return false;
    }

    const auto addressA = itemA.payload<KContacts::Addressee>();
    const auto addressB = itemB.payload<KContacts::Addressee>();
    //
    if (!addressA.name().isEmpty() && !addressB.name().isEmpty()) {
        qCDebug(KADDRESSBOOKMERGELIBPRIVATE_LOG) << " addressB" << addressB.name() << " addressA.name()" << addressA.name();
        if (addressA.name() == addressB.name()) {
            qCDebug(KADDRESSBOOKMERGELIBPRIVATE_LOG) << " return true;";
            return true;
        }
    }
    if (!addressA.nickName().isEmpty() && !addressB.nickName().isEmpty()) {
        if (addressA.nickName() == addressB.nickName()) {
            return true;
        }
    }
    if (!addressA.emails().isEmpty() && !addressB.emails().isEmpty()) {
        const QStringList lstEmails = addressA.emails();
        for (const QString &email : lstEmails) {
            if (addressB.emails().contains(email)) {
                return true;
            }
        }
    }
    return false;
}
