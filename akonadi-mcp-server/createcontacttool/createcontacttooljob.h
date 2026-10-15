/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/tooljobbase.h"
#include <Akonadi/Collection>
#include <KContacts/Addressee>

class CreateContactToolJob : public ToolJobBase
{
    Q_OBJECT
public:
    explicit CreateContactToolJob(QObject *parent = nullptr);
    ~CreateContactToolJob() override;

    void setContact(const KContacts::Addressee &contact);

    void setAddressBookId(Akonadi::Collection::Id id);

    [[nodiscard]] bool canStart() const override;

protected:
    void startJob() override;
    [[nodiscard]] QString invalidArgumentsMessage() const override;

private:
    void slotCollectionFetchResult(KJob *job);
    void slotItemCreateResult(KJob *job);
    void createContact(const Akonadi::Collection &collection);
    KContacts::Addressee mContact;
    Akonadi::Collection::Id mAddressBookId = -1;
};
