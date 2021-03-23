/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "liblanguagetool_private_export.h"

#include <QObject>
class LIBLANGUAGETOOLPRIVATE_TESTS_EXPORT LanguageInfo
{
public:
    LanguageInfo();
    ~LanguageInfo();

    Q_REQUIRED_RESULT QString name() const;
    void setName(const QString &name);

    Q_REQUIRED_RESULT QString longCode() const;
    void setLongCode(const QString &longCode);

    Q_REQUIRED_RESULT QString code() const;
    void setCode(const QString &code);

    Q_REQUIRED_RESULT bool isValid() const;

    void parse(const QJsonObject &obj);

private:
    QString mName;
    QString mLongCode;
    QString mCode;
};
Q_DECLARE_METATYPE(LanguageInfo)
Q_DECLARE_TYPEINFO(LanguageInfo, Q_MOVABLE_TYPE);

