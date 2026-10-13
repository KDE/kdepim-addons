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
class CollectionFetchJob;
}
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolServerToolCall;
}

class ListAddressBooksToolJob : public QObject
{
    Q_OBJECT
public:
    explicit ListAddressBooksToolJob(QObject *parent = nullptr);
    ~ListAddressBooksToolJob() override;

    [[nodiscard]] bool canStart() const;

    void start();

    void setMcpProtocolServerToolCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call);

private:
    void slotResult(KJob *job);
    void slotCancelled();
    QPointer<TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall> mToolCall;
    QPointer<Akonadi::CollectionFetchJob> mFetchJob;
};
