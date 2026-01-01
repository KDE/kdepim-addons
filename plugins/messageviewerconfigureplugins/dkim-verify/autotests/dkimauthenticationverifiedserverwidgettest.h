/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class DKIMAuthenticationVerifiedServerWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit DKIMAuthenticationVerifiedServerWidgetTest(QObject *parent = nullptr);
    ~DKIMAuthenticationVerifiedServerWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
