/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FANCYHEADERSTYLE_H
#define FANCYHEADERSTYLE_H

#include <MessageViewer/HeaderStyle>

#include <headerstyle_util.h>
namespace MessageViewer
{
class HeaderStyleUtil;
class FancyHeaderStyle : public HeaderStyle
{
public:
    FancyHeaderStyle();
    ~FancyHeaderStyle() override;

public:
    const char *name() const override;

    QString format(KMime::Message *message) const override;

private:
    MessageViewer::HeaderStyleUtil mHeaderStyleUtil;
};
}
#endif // FANCYHEADERSTYLE_H
