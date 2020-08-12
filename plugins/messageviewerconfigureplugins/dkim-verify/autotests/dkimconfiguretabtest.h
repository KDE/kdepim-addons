/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef DKIMCONFIGURETABTEST_H
#define DKIMCONFIGURETABTEST_H

#include <QObject>

class DKIMConfigureTabTest : public QObject
{
    Q_OBJECT
public:
    explicit DKIMConfigureTabTest(QObject *parent = nullptr);
    ~DKIMConfigureTabTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // DKIMCONFIGURETABTEST_H
