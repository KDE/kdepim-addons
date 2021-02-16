/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DKIMADVANCEDWIDGETTEST_H
#define DKIMADVANCEDWIDGETTEST_H

#include <QObject>

class DKIMAdvancedWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit DKIMAdvancedWidgetTest(QObject *parent = nullptr);
    ~DKIMAdvancedWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // DKIMADVANCEDWIDGETTEST_H
