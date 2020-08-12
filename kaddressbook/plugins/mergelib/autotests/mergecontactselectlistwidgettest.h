/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MERGECONTACTSELECTLISTWIDGETTEST_H
#define MERGECONTACTSELECTLISTWIDGETTEST_H

#include <QObject>

class MergeContactSelectListWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit MergeContactSelectListWidgetTest(QObject *parent = nullptr);
    ~MergeContactSelectListWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // MERGECONTACTSELECTLISTWIDGETTEST_H
