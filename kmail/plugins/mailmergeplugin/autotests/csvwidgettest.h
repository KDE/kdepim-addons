/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef CSVWIDGETTEST_H
#define CSVWIDGETTEST_H

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

#endif // CSVWIDGETTEST_H
