/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KMime/Message>

class ViewerPluginExternalScriptParseArgument
{
public:
    ViewerPluginExternalScriptParseArgument();

    void setMessage(const std::shared_ptr<KMime::Message> &msg);

    [[nodiscard]] QStringList parse(const QStringList &lst);

    void setAkonadiUrl(const QString &akonadiUrl);

private:
    QString mAkonadiUrl;
    std::shared_ptr<KMime::Message> mMessage;
};
