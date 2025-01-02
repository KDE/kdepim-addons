/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/HeaderStyle>

#include <MessageViewer/HeaderStyle_Util>
namespace MessageViewer
{
class HeaderStyleUtil;
class FancyHeaderStyle : public HeaderStyle
{
public:
    FancyHeaderStyle();
    ~FancyHeaderStyle() override;

public:
    const char *name() const override;

    [[nodiscard]] QString format(KMime::Message *message) const override;

private:
    MessageViewer::HeaderStyleUtil mHeaderStyleUtil;
};
}
