/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef QUICKTEXTCONFIGUREWIDGETTEST_H
#define QUICKTEXTCONFIGUREWIDGETTEST_H

#include <QObject>

class QuickTextConfigureWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit QuickTextConfigureWidgetTest(QObject *parent = nullptr);
    ~QuickTextConfigureWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // QUICKTEXTCONFIGUREWIDGETTEST_H
