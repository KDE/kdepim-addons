/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DKIMAUTHENTICATIONVERIFIEDSERVERDIALOGTEST_H
#define DKIMAUTHENTICATIONVERIFIEDSERVERDIALOGTEST_H

#include <QObject>

class DKIMAuthenticationVerifiedServerDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit DKIMAuthenticationVerifiedServerDialogTest(QObject *parent = nullptr);
    ~DKIMAuthenticationVerifiedServerDialogTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // DKIMAUTHENTICATIONVERIFIEDSERVERDIALOGTEST_H
