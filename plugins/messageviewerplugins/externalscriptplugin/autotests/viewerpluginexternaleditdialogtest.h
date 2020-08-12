/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINEXTERNALEDITDIALOGTEST_H
#define VIEWERPLUGINEXTERNALEDITDIALOGTEST_H

#include <QObject>

class ViewerPluginExternalEditDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalEditDialogTest(QObject *parent = nullptr);
    ~ViewerPluginExternalEditDialogTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // VIEWERPLUGINEXTERNALEDITDIALOGTEST_H
