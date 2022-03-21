/*
   SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class MergeContactsDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit MergeContactsDialogTest(QObject *parent = nullptr);
    ~MergeContactsDialogTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldSwithStackedWidget();
    void initTestCase();
};
