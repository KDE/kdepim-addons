/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef BRIEFHEADERSTRATEGY_H
#define BRIEFHEADERSTRATEGY_H

#include <MessageViewer/HeaderStrategy>
#include <QStringList>

namespace MessageViewer {
class BriefHeaderStrategy : public HeaderStrategy
{
public:
    BriefHeaderStrategy();
    ~BriefHeaderStrategy() override
    {
    }

public:
    const char *name() const override
    {
        return "brief";
    }

    QStringList headersToDisplay() const override
    {
        return mHeadersToDisplay;
    }

    DefaultPolicy defaultPolicy() const override
    {
        return Hide;
    }

private:
    const QStringList mHeadersToDisplay;
};
}
#endif // BRIEFHEADERSTRATEGY_H
