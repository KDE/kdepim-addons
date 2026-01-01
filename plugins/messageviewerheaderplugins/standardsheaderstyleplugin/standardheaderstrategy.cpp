/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "standardheaderstrategy.h"

using namespace MessageViewer;
static const char *const standardHeaders[] = {"subject", "from", "cc", "bcc", "to", "date"};
static const int numStandardHeaders = sizeof standardHeaders / sizeof *standardHeaders;

StandardHeaderStrategy::StandardHeaderStrategy()
    : HeaderStrategy()
    , mHeadersToDisplay(stringList(standardHeaders, numStandardHeaders))
{
}

StandardHeaderStrategy::~StandardHeaderStrategy() = default;
