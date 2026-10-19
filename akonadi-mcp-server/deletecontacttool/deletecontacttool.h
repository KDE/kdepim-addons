/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerTool>

class DeleteContactTool : public TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool
{
public:
    DeleteContactTool();
    ~DeleteContactTool() override;

    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolTool definition() const override;
    void call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call) override;
};
