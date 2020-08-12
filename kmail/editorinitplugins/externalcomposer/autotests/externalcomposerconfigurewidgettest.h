/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef EXTERNALCOMPOSERCONFIGUREWIDGETTEST_H
#define EXTERNALCOMPOSERCONFIGUREWIDGETTEST_H

#include <QObject>

class ExternalComposerConfigureWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ExternalComposerConfigureWidgetTest(QObject *parent = nullptr);
    ~ExternalComposerConfigureWidgetTest() = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldEnableDisableElements();
};

#endif // EXTERNALCOMPOSERCONFIGUREWIDGETTEST_H
