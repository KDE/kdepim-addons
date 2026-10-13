/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>
#include <QPointer>

class KJob;
namespace Akonadi
{
class ContactSearchJob;
}
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolServerToolCall;
}

class ContactSearchToolJob : public QObject
{
    Q_OBJECT
public:
    enum class ContactField : uint8_t {
        None = 0,
        Email = 1,
        Phone = 2,
        Location = 4,
        Birthday = 8,
        All = Email | Phone | Location | Birthday,
    };
    Q_DECLARE_FLAGS(ContactFields, ContactField)
    Q_FLAG(ContactFields)

    explicit ContactSearchToolJob(QObject *parent = nullptr);
    ~ContactSearchToolJob() override;

    void setNameOrEmail(const QString &str);

    void setFields(ContactFields fields);

    [[nodiscard]] bool canStart() const;

    void start();

    void setMcpProtocolServerToolCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call);

private:
    void slotResult(KJob *job);
    void slotCancelled();
    QPointer<TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall> mToolCall;
    QPointer<Akonadi::ContactSearchJob> mSearchJob;
    QString mSearchString;
    ContactFields mFields = ContactField::All;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(ContactSearchToolJob::ContactFields)
