/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/HeaderStrategy>

namespace MessageViewer
{
class GrantleeHeaderStrategy : public HeaderStrategy
{
public:
    GrantleeHeaderStrategy();
    ~GrantleeHeaderStrategy() override;

public:
    const char *name() const override
    {
        return "grantlee";
    }

    DefaultPolicy defaultPolicy() const override
    {
        return Hide;
    }
};
}
