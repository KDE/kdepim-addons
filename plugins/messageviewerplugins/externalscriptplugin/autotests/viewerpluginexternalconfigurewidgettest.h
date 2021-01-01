/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINEXTERNALCONFIGUREWIDGETTEST_H
#define VIEWERPLUGINEXTERNALCONFIGUREWIDGETTEST_H

#include <QObject>

class ViewerPluginExternalConfigureWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalConfigureWidgetTest(QObject *parent = nullptr);
    ~ViewerPluginExternalConfigureWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // VIEWERPLUGINEXTERNALCONFIGUREWIDGETTEST_H
