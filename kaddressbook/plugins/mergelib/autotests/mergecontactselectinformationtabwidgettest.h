/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MERGECONTACTSELECTINFORMATIONTABWIDGETTEST_H
#define MERGECONTACTSELECTINFORMATIONTABWIDGETTEST_H

#include <QObject>

class MergeContactSelectInformationTabWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit MergeContactSelectInformationTabWidgetTest(QObject *parent = nullptr);
    ~MergeContactSelectInformationTabWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAddTab();
};

#endif // MERGECONTACTSELECTINFORMATIONTABWIDGETTEST_H
