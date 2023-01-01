/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ExternalComposerConfigureWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ExternalComposerConfigureWidgetTest(QObject *parent = nullptr);
    ~ExternalComposerConfigureWidgetTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldEnableDisableElements();
};
