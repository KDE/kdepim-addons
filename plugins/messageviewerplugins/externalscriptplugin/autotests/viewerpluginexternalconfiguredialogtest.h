/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINEXTERNALCONFIGUREDIALOGTEST_H
#define VIEWERPLUGINEXTERNALCONFIGUREDIALOGTEST_H

#include <QObject>

class ViewerPluginExternalConfigureDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalConfigureDialogTest(QObject *parent = nullptr);
    ~ViewerPluginExternalConfigureDialogTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // VIEWERPLUGINEXTERNALCONFIGUREDIALOGTEST_H
