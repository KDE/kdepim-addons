/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>
#include <QPointer>

class KJob;
class KLocalizedString;
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolServerToolCall;
}

class ToolJobBase : public QObject
{
    Q_OBJECT
public:
    explicit ToolJobBase(QObject *parent = nullptr);
    ~ToolJobBase() override;

    [[nodiscard]] virtual bool canStart() const;

    void start();

    void setMcpProtocolServerToolCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call);

protected:
    virtual void startJob() = 0;
    [[nodiscard]] virtual QString invalidArgumentsMessage() const;

    // Job killed when the tool call is cancelled
    void setCurrentJob(KJob *job);
    // Returns false and finishes when the tool call is gone or the job failed
    [[nodiscard]] bool checkJobResult(KJob *job, const KLocalizedString &errorMessage);
    [[nodiscard]] bool hasToolCall() const;
    void finish(const QString &text, bool isError = false);

private:
    void slotCancelled();
    QPointer<TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall> mToolCall;
    QPointer<KJob> mCurrentJob;
};
