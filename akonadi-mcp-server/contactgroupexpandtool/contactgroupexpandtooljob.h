/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <KContacts/ContactGroup>
#include <QObject>
#include <QPointer>
#include <QStringList>

class KJob;
namespace Akonadi
{
class ContactGroupSearchJob;
class ContactGroupExpandJob;
}
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolServerToolCall;
}

class ContactGroupExpandToolJob : public QObject
{
    Q_OBJECT
public:
    explicit ContactGroupExpandToolJob(QObject *parent = nullptr);
    ~ContactGroupExpandToolJob() override;

    void setGroupName(const QString &str);

    [[nodiscard]] bool canStart() const;

    void start();

    void setMcpProtocolServerToolCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call);

private:
    void slotResult(KJob *job);
    void slotExpandResult(KJob *job);
    void slotCancelled();
    void expandNextGroup();
    void finish(const QString &text, bool isError = false);
    QPointer<TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall> mToolCall;
    QPointer<Akonadi::ContactGroupSearchJob> mSearchJob;
    QPointer<Akonadi::ContactGroupExpandJob> mExpandJob;
    KContacts::ContactGroup::List mContactGroups;
    QStringList mEntries;
    QString mSearchString;
};
