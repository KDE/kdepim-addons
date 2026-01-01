/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class SearchDuplicateResultWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit SearchDuplicateResultWidgetTest(QObject *parent = nullptr);
    ~SearchDuplicateResultWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldHaveMergeButtonEnabled();
};
