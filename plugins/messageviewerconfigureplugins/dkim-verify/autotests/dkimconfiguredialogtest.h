/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DKIMCONFIGUREDIALOGTEST_H
#define DKIMCONFIGUREDIALOGTEST_H

#include <QObject>

class DKIMConfigureDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit DKIMConfigureDialogTest(QObject *parent = nullptr);
    ~DKIMConfigureDialogTest() = default;

private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // DKIMCONFIGUREDIALOGTEST_H
