/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef InsertEmailPLUGINEDITORINTERFACETEST_H
#define InsertEmailPLUGINEDITORINTERFACETEST_H

#include <QObject>

class InsertEmailPluginEditorInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit InsertEmailPluginEditorInterfaceTest(QObject *parent = nullptr);
    ~InsertEmailPluginEditorInterfaceTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif
