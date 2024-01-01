/*
    SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

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

    [[nodiscard]] QList<Akonadi::Item::List> potentialDuplicateContacts() const;

Q_SIGNALS:
    void finished(const QList<Akonadi::Item::List> &);

private:
    [[nodiscard]] Akonadi::Item::List checkList(const Akonadi::Item::List &lstItem);
    [[nodiscard]] bool isDuplicate(const Akonadi::Item &itemA, const Akonadi::Item &itemB);
    const Akonadi::Item::List mListItem;
    QList<Akonadi::Item::List> mListDuplicate;
};
}
