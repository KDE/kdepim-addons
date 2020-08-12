/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAMMALECTECONFIGDIALOGTEST_H
#define GRAMMALECTECONFIGDIALOGTEST_H

#include <QObject>

class GrammalecteConfigDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit GrammalecteConfigDialogTest(QObject *parent = nullptr);
    ~GrammalecteConfigDialogTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // GRAMMALECTECONFIGDIALOGTEST_H
