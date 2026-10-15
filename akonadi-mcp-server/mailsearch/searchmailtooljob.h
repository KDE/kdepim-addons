/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>
#include <QPointer>
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolServerToolCall;
}
class SearchMailToolJob : public QObject
{
    Q_OBJECT
public:
    explicit SearchMailToolJob(QObject *parent = nullptr);
    ~SearchMailToolJob() override;
    [[nodiscard]] bool canStart() const;

    void start();

    void setMcpProtocolServerToolCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call);

private:
    QPointer<TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall> mToolCall;
};
