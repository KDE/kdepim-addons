/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include <QObject>

class CsvWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit CsvWidgetTest(QObject *parent = nullptr);
    ~CsvWidgetTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldChangePath();
};
