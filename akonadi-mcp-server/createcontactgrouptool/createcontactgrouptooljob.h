/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/tooljobbase.h"
#include <Akonadi/Collection>
#include <Akonadi/Item>
#include <KContacts/ContactGroup>
#include <QStringList>

class CreateContactGroupToolJob : public ToolJobBase
{
    Q_OBJECT
public:
    explicit CreateContactGroupToolJob(QObject *parent = nullptr);
    ~CreateContactGroupToolJob() override;

    void setName(const QString &name);
    // Members which are stored in an address book, added as references
    void setContactIds(const QList<Akonadi::Item::Id> &contactIds);
    // Members which are not in an address book, added as data
    void setEmails(const QStringList &emails);
    void setAddressBookId(Akonadi::Collection::Id id);

    [[nodiscard]] bool canStart() const override;

protected:
    void startJob() override;
    [[nodiscard]] QString invalidArgumentsMessage() const override;

private:
    void slotContactFetchResult(KJob *job);
    void fetchAddressBook();
    void slotCollectionFetchResult(KJob *job);
    void createContactGroup(const Akonadi::Collection &collection);
    void slotItemCreateResult(KJob *job);
    KContacts::ContactGroup mContactGroup;
    QString mName;
    QList<Akonadi::Item::Id> mContactIds;
    QStringList mEmails;
    Akonadi::Collection::Id mAddressBookId = -1;
};
