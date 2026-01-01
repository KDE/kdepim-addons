/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class DKIMPolicyWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit DKIMPolicyWidgetTest(QObject *parent = nullptr);
    ~DKIMPolicyWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
