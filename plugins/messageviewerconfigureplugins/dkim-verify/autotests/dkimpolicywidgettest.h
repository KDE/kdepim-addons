/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DKIMPOLICYWIDGETTEST_H
#define DKIMPOLICYWIDGETTEST_H

#include <QObject>

class DKIMPolicyWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit DKIMPolicyWidgetTest(QObject *parent = nullptr);
    ~DKIMPolicyWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // DKIMPOLICYWIDGETTEST_H
