/*  -*- c++ -*-
    messageviewer/headerstyle.h

    This file is part of KMail, the KDE mail client.
    SPDX-FileCopyrightText: 2003 Marc Mutz <mutz@kde.org>
    SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef BRIEFHEADERSTYLE_H
#define BRIEFHEADERSTYLE_H

#include <MessageViewer/HeaderStyle>
#include "headerstyle_util.h"
namespace MessageViewer {
class BriefHeaderStyle : public HeaderStyle
{
public:
    BriefHeaderStyle() : HeaderStyle()
    {
    }

    ~BriefHeaderStyle() override
    {
    }

public:
    const char *name() const override
    {
        return "brief";
    }

private:
    QString format(KMime::Message *message) const override;
    MessageViewer::HeaderStyleUtil mHeaderStyleUtil;
};
}

#endif // BRIEFHEADERSTYLE_H
