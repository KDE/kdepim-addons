/*
    SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <AkonadiCore/Item>
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
    Akonadi::Item::List checkList(const Akonadi::Item::List &lstItem);
    bool isDuplicate(const Akonadi::Item &itemA, const Akonadi::Item &itemB);
    Akonadi::Item::List mListItem;
    QVector<Akonadi::Item::List> mListDuplicate;
};
}

