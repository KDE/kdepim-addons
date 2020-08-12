/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MERGECONTACTSELECTINFORMATIONWIDGETTEST_H
#define MERGECONTACTSELECTINFORMATIONWIDGETTEST_H

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

#endif // MERGECONTACTSELECTINFORMATIONWIDGETTEST_H
