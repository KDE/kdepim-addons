/*
    SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include <QObject>

#include <Akonadi/Collection>
#include <Akonadi/Item>
#include <KContacts/Addressee>
namespace KABMergeContacts
{
class MergeContactsJob : public QObject
{
    Q_OBJECT
public:
    explicit MergeContactsJob(QObject *parent = nullptr);
    ~MergeContactsJob() override;

    void start();

    void setListItem(const Akonadi::Item::List &lstItem);

    void setDestination(const Akonadi::Collection &collection);

    [[nodiscard]] bool canStart() const;

    void setNewContact(const KContacts::Addressee &addr);

Q_SIGNALS:
    void finished(const Akonadi::Item &item);

private:
    void slotCreateMergedContactFinished(KJob *job);
    void slotDeleteContactsFinished(KJob *job);
    void generateMergedContact();
    void createMergedContact(const KContacts::Addressee &addressee);

    Akonadi::Collection mCollection;
    Akonadi::Item::List mListItem;
    Akonadi::Item mCreatedContact;
    KContacts::Addressee mNewContact;
};
}
