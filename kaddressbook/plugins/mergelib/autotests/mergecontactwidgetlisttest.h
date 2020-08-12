/*
   SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MERGECONTACTWIDGETLISTTEST_H
#define MERGECONTACTWIDGETLISTTEST_H

#include <QObject>

class MergeContactWidgetListTest : public QObject
{
    Q_OBJECT
public:
    explicit MergeContactWidgetListTest(QObject *parent = nullptr);
    ~MergeContactWidgetListTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldCleanListWhenSetItems();
};

#endif // MERGECONTACTWIDGETLISTTEST_H
