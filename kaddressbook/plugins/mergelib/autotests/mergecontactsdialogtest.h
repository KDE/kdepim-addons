/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MERGECONTACTSDIALOGTEST_H
#define MERGECONTACTSDIALOGTEST_H

#include <QObject>

class MergeContactsDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit MergeContactsDialogTest(QObject *parent = nullptr);
    ~MergeContactsDialogTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldSwithStackedWidget();
    void initTestCase();
};

#endif // MERGECONTACTSDIALOGTEST_H
