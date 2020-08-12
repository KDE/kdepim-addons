/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINEXTERNALEDITWIDGETTEST_H
#define VIEWERPLUGINEXTERNALEDITWIDGETTEST_H

#include <QObject>

class ViewerPluginExternalEditWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalEditWidgetTest(QObject *parent = nullptr);
    ~ViewerPluginExternalEditWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldGetSaveInfo();
    void shouldGetSaveInfo_data();
};

#endif // VIEWERPLUGINEXTERNALEDITWIDGETTEST_H
