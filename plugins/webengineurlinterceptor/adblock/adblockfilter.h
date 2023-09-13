/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "adblockplugin_private_export.h"
#include <QDebug>
#include <QString>

class LIBADBLOCKPLUGIN_TESTS_EXPORT AdblockFilter
{
public:
    AdblockFilter();
    ~AdblockFilter();

    Q_REQUIRED_RESULT QString url() const;
    void setUrl(const QString &newUrl);

    Q_REQUIRED_RESULT QString name() const;
    void setName(const QString &newName);

private:
    QString mUrl;
    QString mName;
};
Q_DECLARE_TYPEINFO(AdblockFilter, Q_RELOCATABLE_TYPE);
LIBADBLOCKPLUGIN_TESTS_EXPORT QDebug operator<<(QDebug d, const AdblockFilter &t);
