/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <Akonadi/Collection>
#include <KContacts/Addressee>
#include <QObject>
#include <QPointer>

class KJob;
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolServerToolCall;
}

class CreateContactToolJob : public QObject
{
    Q_OBJECT
public:
    explicit CreateContactToolJob(QObject *parent = nullptr);
    ~CreateContactToolJob() override;

    void setContact(const KContacts::Addressee &contact);

    void setAddressBookId(Akonadi::Collection::Id id);

    [[nodiscard]] bool canStart() const;

    void start();

    void setMcpProtocolServerToolCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call);

private:
    void slotCollectionFetchResult(KJob *job);
    void slotItemCreateResult(KJob *job);
    void slotCancelled();
    void createContact(const Akonadi::Collection &collection);
    QPointer<TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall> mToolCall;
    QPointer<KJob> mCurrentJob;
    KContacts::Addressee mContact;
    Akonadi::Collection::Id mAddressBookId = -1;
};
