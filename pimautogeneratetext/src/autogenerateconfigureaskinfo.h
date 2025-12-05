/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "pimautogeneratetext_export.h"
#include <QMetaType>
#include <QString>
class QDebug;
class PIMAUTOGENERATETEXT_EXPORT AutogenerateConfigureAskInfo
{
public:
    AutogenerateConfigureAskInfo();
    ~AutogenerateConfigureAskInfo();

    [[nodiscard]] bool enabled() const;
    void setEnabled(bool newEnabled);

    [[nodiscard]] QString text() const;
    void setText(const QString &newText);

    [[nodiscard]] QString title() const;
    void setTitle(const QString &newTitle);

    [[nodiscard]] bool operator==(const AutogenerateConfigureAskInfo &other) const;

private:
    QString mTitle;
    QString mText;
    bool mEnabled = true;
};
Q_DECLARE_METATYPE(AutogenerateConfigureAskInfo)
Q_DECLARE_TYPEINFO(AutogenerateConfigureAskInfo, Q_RELOCATABLE_TYPE);
PIMAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const AutogenerateConfigureAskInfo &t);
