/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MERGECONTACTSELECTINFORMATIONSCROLLAREATEST_H
#define MERGECONTACTSELECTINFORMATIONSCROLLAREATEST_H

#include <QObject>

class MergeContactSelectInformationScrollAreaTest : public QObject
{
    Q_OBJECT
public:
    explicit MergeContactSelectInformationScrollAreaTest(QObject *parent = nullptr);
    ~MergeContactSelectInformationScrollAreaTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // MERGECONTACTSELECTINFORMATIONSCROLLAREATEST_H
