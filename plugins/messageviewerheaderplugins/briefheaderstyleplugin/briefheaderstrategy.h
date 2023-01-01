/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

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

    Q_REQUIRED_RESULT QStringList headersToDisplay() const override
    {
        return mHeadersToDisplay;
    }

    Q_REQUIRED_RESULT DefaultPolicy defaultPolicy() const override
    {
        return Hide;
    }

private:
    const QStringList mHeadersToDisplay;
};
}
