/*
   SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <MessageViewer/HeaderStyle>

#include <MessageViewer/HeaderStyle_Util>
namespace MessageViewer
{
class EnterpriseHeaderStyle : public HeaderStyle
{
public:
    EnterpriseHeaderStyle()
        : HeaderStyle()
    {
    }

    ~EnterpriseHeaderStyle() override = default;

    const char *name() const override;

    [[nodiscard]] QString format(KMime::Message *message) const override;

private:
    mutable QColor mActiveColor;
    MessageViewer::HeaderStyleUtil mHeaderStyleUtil;
};
}
