/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class MergeContactSelectInformationWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit MergeContactSelectInformationWidgetTest(QObject *parent = nullptr);
    ~MergeContactSelectInformationWidgetTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
};

