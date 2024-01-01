/*
   SPDX-FileCopyrightText: 2018-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class DKIMConfigureDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit DKIMConfigureDialogTest(QObject *parent = nullptr);
    ~DKIMConfigureDialogTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValue();
};
