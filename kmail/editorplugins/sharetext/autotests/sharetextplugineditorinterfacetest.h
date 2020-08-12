/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef ShareTextPLUGINEDITORINTERFACETEST_H
#define ShareTextPLUGINEDITORINTERFACETEST_H

#include <QObject>

class ShareTextPluginEditorInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit ShareTextPluginEditorInterfaceTest(QObject *parent = nullptr);
    ~ShareTextPluginEditorInterfaceTest();
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif
