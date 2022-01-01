/*
   SPDX-FileCopyrightText: 2016-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KMime/Message>

class ViewerPluginExternalScriptParseArgument
{
public:
    ViewerPluginExternalScriptParseArgument();

    void setMessage(const KMime::Message::Ptr &msg);

    Q_REQUIRED_RESULT QStringList parse(const QStringList &lst);

    void setAkonadiUrl(const QString &akonadiUrl);

private:
    QString mAkonadiUrl;
    KMime::Message::Ptr mMessage;
};

