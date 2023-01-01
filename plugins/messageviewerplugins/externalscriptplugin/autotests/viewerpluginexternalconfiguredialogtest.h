/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ViewerPluginExternalConfigureDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalConfigureDialogTest(QObject *parent = nullptr);
    ~ViewerPluginExternalConfigureDialogTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};
