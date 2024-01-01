/*
   SPDX-FileCopyrightText: 2014-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class MergeContactInfoWidgetTest : public QObject
{
    Q_OBJECT
public:
    MergeContactInfoWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValueOnCreation();
    void shouldHaveActivateDisplayWidgetWhenSelectOneContact();
    void shouldHaveActivateNoWidgetWhenSelectNoContact();
    void initTestCase();
};
