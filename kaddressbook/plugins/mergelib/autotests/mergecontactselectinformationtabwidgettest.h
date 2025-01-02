/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class MergeContactSelectInformationTabWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit MergeContactSelectInformationTabWidgetTest(QObject *parent = nullptr);
    ~MergeContactSelectInformationTabWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAddTab();
};
