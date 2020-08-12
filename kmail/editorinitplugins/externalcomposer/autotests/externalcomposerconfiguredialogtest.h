/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef EXTERNALCOMPOSERCONFIGUREDIALOGTEST_H
#define EXTERNALCOMPOSERCONFIGUREDIALOGTEST_H

#include <QObject>

class ExternalComposerConfigureDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit ExternalComposerConfigureDialogTest(QObject *parent = nullptr);
    ~ExternalComposerConfigureDialogTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // EXTERNALCOMPOSERCONFIGUREDIALOGTEST_H
