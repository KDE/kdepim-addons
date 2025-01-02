/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/HeaderStrategy>
#include <QStringList>

namespace MessageViewer
{
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
