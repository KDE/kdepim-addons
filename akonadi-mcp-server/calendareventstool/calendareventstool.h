/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/toolbase.h"

class CalendarEventsTool : public ToolBase
{
public:
    CalendarEventsTool();
    ~CalendarEventsTool() override;

    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolTool definition() const override;

private:
    void doCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call) override;
};
