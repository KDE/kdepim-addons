/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRANTLEEHEADERSTRATEGY_H
#define GRANTLEEHEADERSTRATEGY_H

#include <MessageViewer/HeaderStrategy>

namespace MessageViewer {
class GrantleeHeaderStrategy : public HeaderStrategy
{
public:
    GrantleeHeaderStrategy();
    ~GrantleeHeaderStrategy();

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
#endif // GRANTLEEHEADERSTRATEGY_H
