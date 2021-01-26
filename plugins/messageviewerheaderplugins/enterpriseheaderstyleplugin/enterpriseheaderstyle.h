/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef ENTERPRISEHEADERSTYLE_H
#define ENTERPRISEHEADERSTYLE_H

#include <MessageViewer/HeaderStyle>

#include <headerstyle_util.h>
namespace MessageViewer
{
class EnterpriseHeaderStyle : public HeaderStyle
{
public:
    EnterpriseHeaderStyle()
        : HeaderStyle()
    {
    }

    ~EnterpriseHeaderStyle() override
    {
    }

    const char *name() const override;

    QString format(KMime::Message *message) const override;

private:
    MessageViewer::HeaderStyleUtil mHeaderStyleUtil;
};
}

#endif // ENTERPRISEHEADERSTYLE_H
