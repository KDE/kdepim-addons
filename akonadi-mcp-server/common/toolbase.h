/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#ifdef HAVE_MCP_CONFIRMATION_TOOL
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerConfirmationTool>

class ToolBase : public TextAutoGenerateTextMcpProtocolCore::McpProtocolServerConfirmationTool
{
public:
    ToolBase();
    ~ToolBase() override;

protected:
    [[nodiscard]] bool askModify() const override;
};
#else
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerTool>

class ToolBase : public TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool
{
public:
    ToolBase();
    ~ToolBase() override;

    void call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call) final;

private:
    virtual void doCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call) = 0;
};
#endif
