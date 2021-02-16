/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

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
    ~GrammalecteConfigDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // GRAMMALECTECONFIGDIALOGTEST_H
