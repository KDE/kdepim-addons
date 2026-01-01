/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "adblockplugin_private_export.h"
#include <QMetaType>
#include <QString>
class QDebug;
class LIBADBLOCKPLUGIN_TESTS_EXPORT AdblockFilter
{
public:
    AdblockFilter();
    ~AdblockFilter();

    [[nodiscard]] QString url() const;
    void setUrl(const QString &newUrl);

    [[nodiscard]] QString name() const;
    void setName(const QString &newName);

    [[nodiscard]] bool operator==(const AdblockFilter &other) const;

private:
    QString mUrl;
    QString mName;
};
Q_DECLARE_TYPEINFO(AdblockFilter, Q_RELOCATABLE_TYPE);
LIBADBLOCKPLUGIN_TESTS_EXPORT QDebug operator<<(QDebug d, const AdblockFilter &t);
