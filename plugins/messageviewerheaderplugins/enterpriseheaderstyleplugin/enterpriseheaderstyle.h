/*
   SPDX-FileCopyrightText: 2013-2022 Laurent Montel <montel@kde.org>

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

    QString format(KMime::Message *message) const override;

private:
    MessageViewer::HeaderStyleUtil mHeaderStyleUtil;
};
}

