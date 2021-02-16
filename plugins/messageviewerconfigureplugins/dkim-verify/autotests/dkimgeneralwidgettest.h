/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DKIMGENERALWIDGETTEST_H
#define DKIMGENERALWIDGETTEST_H

#include <QObject>

class DKIMGeneralWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit DKIMGeneralWidgetTest(QObject *parent = nullptr);
    ~DKIMGeneralWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // DKIMGENERALWIDGETTEST_H
