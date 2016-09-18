/*
   Copyright (C) 2015-2016 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "standardheaderstrategy.h"

using namespace MessageViewer;
static const char *const standardHeaders[] = {
    "subject", "from", "cc", "bcc", "to"
};
static const int numStandardHeaders = sizeof standardHeaders / sizeof * standardHeaders;

StandardHeaderStrategy::StandardHeaderStrategy()
    : HeaderStrategy(),
      mHeadersToDisplay(stringList(standardHeaders, numStandardHeaders))
{

}

StandardHeaderStrategy::~StandardHeaderStrategy()
{

}
