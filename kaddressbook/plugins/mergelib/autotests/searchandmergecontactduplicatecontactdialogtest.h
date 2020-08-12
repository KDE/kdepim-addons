/*
   SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MERGECONTACTDUPLICATECONTACTDIALOGTEST_H
#define MERGECONTACTDUPLICATECONTACTDIALOGTEST_H

#include <QObject>

class SearchAndMergeContactDuplicateContactDialogTest : public QObject
{
    Q_OBJECT
public:
    SearchAndMergeContactDuplicateContactDialogTest(QObject *parent = nullptr);

private Q_SLOTS:
    void shouldHaveDefaultValueOnCreation();
    void shouldShowNoEnoughPageWhenSelectOneContact();
    void shouldShowNoContactWhenListIsEmpty();
    void initTestCase();
};

#endif // MERGECONTACTDUPLICATECONTACTDIALOGTEST_H
