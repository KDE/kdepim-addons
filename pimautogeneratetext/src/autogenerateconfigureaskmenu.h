/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "pimautogeneratetext_export.h"
#include <QObject>

class PIMAUTOGENERATETEXT_EXPORT AutogenerateConfigureAskMenu : public QObject
{
    Q_OBJECT
public:
    explicit AutogenerateConfigureAskMenu(QObject *parent = nullptr);
    ~AutogenerateConfigureAskMenu() override;

Q_SIGNALS:
    void askRequested(const QString &msg);
};
