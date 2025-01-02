/*  -*- c++ -*-
    messageviewer/headerstyle.h

    This file is part of KMail, the KDE mail client.
    SPDX-FileCopyrightText: 2003 Marc Mutz <mutz@kde.org>
    SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include <MessageViewer/HeaderStyle>
#include <MessageViewer/HeaderStyle_Util>
namespace MessageViewer
{
class BriefHeaderStyle : public HeaderStyle
{
public:
    BriefHeaderStyle()
        : HeaderStyle()
    {
    }

    ~BriefHeaderStyle() override = default;

public:
    const char *name() const override
    {
        return "brief";
    }

private:
    [[nodiscard]] QString format(KMime::Message *message) const override;
    MessageViewer::HeaderStyleUtil mHeaderStyleUtil;
};
}
