/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DKIMAUTHENTICATIONVERIFIEDSERVERWIDGETTEST_H
#define DKIMAUTHENTICATIONVERIFIEDSERVERWIDGETTEST_H

#include <QObject>

class DKIMAuthenticationVerifiedServerWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit DKIMAuthenticationVerifiedServerWidgetTest(QObject *parent = nullptr);
    ~DKIMAuthenticationVerifiedServerWidgetTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // DKIMAUTHENTICATIONVERIFIEDSERVERWIDGETTEST_H
