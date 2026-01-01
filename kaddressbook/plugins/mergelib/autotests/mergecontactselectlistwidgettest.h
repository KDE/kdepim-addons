/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class MergeContactSelectListWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit MergeContactSelectListWidgetTest(QObject *parent = nullptr);
    ~MergeContactSelectListWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};
