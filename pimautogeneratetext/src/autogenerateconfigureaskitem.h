/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <QString>

class AutogenerateConfigureAskItem
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
