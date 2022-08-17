/*
    SPDX-FileCopyrightText: 2013-2022 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <Akonadi/Item>
#include <QObject>

namespace KABMergeContacts
{
class SearchPotentialDuplicateContactJob : public QObject
{
    Q_OBJECT
public:
    explicit SearchPotentialDuplicateContactJob(const Akonadi::Item::List &list, QObject *parent = nullptr);
    ~SearchPotentialDuplicateContactJob() override;

    void start();

    Q_REQUIRED_RESULT QVector<Akonadi::Item::List> potentialDuplicateContacts() const;

Q_SIGNALS:
    void finished(const QVector<Akonadi::Item::List> &);

private:
    Q_REQUIRED_RESULT Akonadi::Item::List checkList(const Akonadi::Item::List &lstItem);
    Q_REQUIRED_RESULT bool isDuplicate(const Akonadi::Item &itemA, const Akonadi::Item &itemB);
    const Akonadi::Item::List mListItem;
    QVector<Akonadi::Item::List> mListDuplicate;
};
}
