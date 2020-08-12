/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef RESULTDUPLICATETREEWIDGETTEST_H
#define RESULTDUPLICATETREEWIDGETTEST_H

#include <QObject>

class ResultDuplicateTreeWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ResultDuplicateTreeWidgetTest(QObject *parent = nullptr);
    ~ResultDuplicateTreeWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldFillList();
    void shouldClearList();
    void shouldEmptyListIfNotContactSelected();
    void shouldReturnNotEmptyContactList();
    void shouldNotReturnListWhenJustOneChildSelected();
    void shouldReturnTwoLists();
    void shouldReturnJustOnList();
};

#endif // RESULTDUPLICATETREEWIDGETTEST_H
