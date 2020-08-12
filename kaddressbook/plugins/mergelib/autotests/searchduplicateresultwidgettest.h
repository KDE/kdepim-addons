/*
   SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SEARCHDUPLICATERESULTWIDGETTEST_H
#define SEARCHDUPLICATERESULTWIDGETTEST_H

#include <QObject>

class SearchDuplicateResultWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit SearchDuplicateResultWidgetTest(QObject *parent = nullptr);
    ~SearchDuplicateResultWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldHaveMergeButtonEnabled();
};

#endif // SEARCHDUPLICATERESULTWIDGETTEST_H
