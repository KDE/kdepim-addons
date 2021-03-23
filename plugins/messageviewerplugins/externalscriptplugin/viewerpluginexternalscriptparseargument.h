/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KMime/Message>

class ViewerPluginExternalScriptParseArgument
{
public:
    ViewerPluginExternalScriptParseArgument();

    void setMessage(const KMime::Message::Ptr &msg);

    QStringList parse(const QStringList &lst);

private:
    KMime::Message::Ptr mMessage;
};

