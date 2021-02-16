/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAMMALECTECONFIGWIDGETTEST_H
#define GRAMMALECTECONFIGWIDGETTEST_H

#include <QObject>

class GrammalecteConfigWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit GrammalecteConfigWidgetTest(QObject *parent = nullptr);
    ~GrammalecteConfigWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // GRAMMALECTECONFIGWIDGETTEST_H
