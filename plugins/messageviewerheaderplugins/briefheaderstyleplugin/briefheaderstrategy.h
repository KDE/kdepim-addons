/*
   SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/HeaderStrategy>
#include <QStringList>

namespace MessageViewer
{
class BriefHeaderStrategy : public HeaderStrategy
{
public:
    BriefHeaderStrategy();
    ~BriefHeaderStrategy() override = default;

public:
    const char *name() const override
    {
        return "brief";
    }

    [[nodiscard]] QStringList headersToDisplay() const override
    {
        return mHeadersToDisplay;
    }

    [[nodiscard]] DefaultPolicy defaultPolicy() const override
    {
        return Hide;
    }

private:
    const QStringList mHeadersToDisplay;
};
}
