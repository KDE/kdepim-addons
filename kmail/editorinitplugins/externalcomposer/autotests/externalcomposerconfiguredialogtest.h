/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ExternalComposerConfigureDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit ExternalComposerConfigureDialogTest(QObject *parent = nullptr);
    ~ExternalComposerConfigureDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
