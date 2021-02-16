/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DKIMCONFIGUREWIDGETTEST_H
#define DKIMCONFIGUREWIDGETTEST_H

#include <QObject>

class DKIMConfigureWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit DKIMConfigureWidgetTest(QObject *parent = nullptr);
    ~DKIMConfigureWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // DKIMCONFIGUREWIDGETTEST_H
