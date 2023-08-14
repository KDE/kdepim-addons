/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QString>

class AdblockFilter
{
public:
    AdblockFilter();
    ~AdblockFilter();

    Q_REQUIRED_RESULT QString url() const;
    void setUrl(const QString &newUrl);

private:
    QString mUrl;
};
