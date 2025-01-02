/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ResultDuplicateTreeWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ResultDuplicateTreeWidgetTest(QObject *parent = nullptr);
    ~ResultDuplicateTreeWidgetTest() override;
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
