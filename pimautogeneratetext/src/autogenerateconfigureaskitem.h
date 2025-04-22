/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "pimautogeneratetext_private_export.h"
#include <QDebug>
#include <QString>
class PIMAUTOGENERATETEXT_TESTS_EXPORT AutogenerateConfigureAskItem
{
public:
    AutogenerateConfigureAskItem();
    ~AutogenerateConfigureAskItem();

    [[nodiscard]] bool enabled() const;
    void setEnabled(bool newEnabled);

    [[nodiscard]] QString text() const;
    void setText(const QString &newText);

private:
    QString mText;
    bool mEnabled = true;
};
Q_DECLARE_METATYPE(AutogenerateConfigureAskItem)
Q_DECLARE_TYPEINFO(AutogenerateConfigureAskItem, Q_RELOCATABLE_TYPE);
PIMAUTOGENERATETEXT_TESTS_EXPORT QDebug operator<<(QDebug d, const AutogenerateConfigureAskItem &t);
