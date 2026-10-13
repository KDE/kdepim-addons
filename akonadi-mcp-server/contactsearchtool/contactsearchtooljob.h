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
    explicit ContactSearchToolJob(QObject *parent = nullptr);
    ~ContactSearchToolJob() override;

    void setNameOrEmail(const QString &str);

    [[nodiscard]] bool canStart() const;

    void start();

    void setMcpProtocolServerToolCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call);

private:
    void slotResult(KJob *job);
    void slotCancelled();
    QPointer<TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall> mToolCall;
    QPointer<Akonadi::ContactSearchJob> mSearchJob;
    QString mSearchString;
};
