/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "pimautogeneratetext_private_export.h"
#include <QObject>

class PIMAUTOGENERATETEXT_TESTS_EXPORT AutogenerateConfigureAskManager : public QObject
{
    Q_OBJECT
public:
    explicit AutogenerateConfigureAskManager(QObject *parent = nullptr);
    ~AutogenerateConfigureAskManager() override;

    void load();
    void save();
};
