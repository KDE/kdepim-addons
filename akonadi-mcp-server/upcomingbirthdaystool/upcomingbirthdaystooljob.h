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
class RecursiveItemFetchJob;
}
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolServerToolCall;
}

class UpcomingBirthdaysToolJob : public QObject
{
    Q_OBJECT
public:
    explicit UpcomingBirthdaysToolJob(QObject *parent = nullptr);
    ~UpcomingBirthdaysToolJob() override;

    void setDays(int days);

    [[nodiscard]] bool canStart() const;

    void start();

    void setMcpProtocolServerToolCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call);

private:
    void slotResult(KJob *job);
    void slotCancelled();
    QPointer<TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall> mToolCall;
    QPointer<Akonadi::RecursiveItemFetchJob> mFetchJob;
    int mDays = 30;
};
