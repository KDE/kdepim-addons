/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DKIMKEYRECORDWIDGETTEST_H
#define DKIMKEYRECORDWIDGETTEST_H

#include <QObject>

class DKIMKeyRecordWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit DKIMKeyRecordWidgetTest(QObject *parent = nullptr);
    ~DKIMKeyRecordWidgetTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // DKIMKEYRECORDWIDGETTEST_H
