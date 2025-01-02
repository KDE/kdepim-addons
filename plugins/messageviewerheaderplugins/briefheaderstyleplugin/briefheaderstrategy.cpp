/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "briefheaderstrategy.h"
using namespace MessageViewer;

static const char *const briefHeaders[] = {"subject", "from", "cc", "bcc", "date"};
static const int numBriefHeaders = sizeof briefHeaders / sizeof *briefHeaders;

BriefHeaderStrategy::BriefHeaderStrategy()
    : HeaderStrategy()
    , mHeadersToDisplay(stringList(briefHeaders, numBriefHeaders))
{
}
