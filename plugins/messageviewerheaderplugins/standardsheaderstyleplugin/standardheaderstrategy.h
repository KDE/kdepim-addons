/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef STANDARDHEADERSTRATEGY_H
#define STANDARDHEADERSTRATEGY_H

#include <MessageViewer/HeaderStrategy>
#include <QStringList>

namespace MessageViewer {
//
// StandardHeaderStrategy:
//   BCC, CC, Date, From, Subject, To
//

class StandardHeaderStrategy : public HeaderStrategy
{
public:
    StandardHeaderStrategy();
    ~StandardHeaderStrategy() override;

public:
    const char *name() const override
    {
        return "standard";
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
#endif // STANDARDHEADERSTRATEGY_H
