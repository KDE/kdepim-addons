/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <Akonadi/Item>
#include <QObject>

class MergeContactWidgetTest : public QObject
{
    Q_OBJECT
public:
    MergeContactWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValueOnCreation();
    void shouldFillList();
    void shouldFillListWithValidItem();
    void shouldEnableButton();
    void shouldEmitSignalsWhenThereIsElementSelected();
    void shouldEmitSignalsWhenThereIsTwoElementsSelected();
    void shouldEmitSignalsWhenSelectContact();

private:
    Akonadi::Item::List createItems();
};
