/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerTool>

class ContactGroupExpandTool : public TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool
{
public:
    ContactGroupExpandTool();
    ~ContactGroupExpandTool() override;

    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolTool definition() const override;
    void call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call) override;
};
