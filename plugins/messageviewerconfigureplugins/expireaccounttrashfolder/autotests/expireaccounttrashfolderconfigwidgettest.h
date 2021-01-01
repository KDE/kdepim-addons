/*
   SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef EXPIREACCOUNTTRASHFOLDERCONFIGWIDGETTEST_H
#define EXPIREACCOUNTTRASHFOLDERCONFIGWIDGETTEST_H

#include <QObject>

class ExpireAccountTrashFolderConfigWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ExpireAccountTrashFolderConfigWidgetTest(QObject *parent = nullptr);
    ~ExpireAccountTrashFolderConfigWidgetTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // EXPIREACCOUNTTRASHFOLDERCONFIGWIDGETTEST_H
