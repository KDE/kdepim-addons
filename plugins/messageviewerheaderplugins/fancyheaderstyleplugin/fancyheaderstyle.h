/*
   Copyright (C) 2013-2018 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef FANCYHEADERSTYLE_H
#define FANCYHEADERSTYLE_H

#include "messageviewer/headerstyle.h"

#include <headerstyle_util.h>
namespace MessageViewer {
class HeaderStyleUtil;
class FancyHeaderStyle : public HeaderStyle
{
public:
    FancyHeaderStyle();
    ~FancyHeaderStyle() override;

public:
    const char *name() const override;

    QString format(KMime::Message *message) const override;

    bool hasAttachmentQuickList() const override;
private:
    MessageViewer::HeaderStyleUtil mHeaderStyleUtil;
};
}
#endif // FANCYHEADERSTYLE_H
