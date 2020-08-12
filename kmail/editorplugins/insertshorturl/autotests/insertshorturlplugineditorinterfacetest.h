/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef InsertShorturlPLUGINEDITORINTERFACETEST_H
#define InsertShorturlPLUGINEDITORINTERFACETEST_H

#include <QObject>

class InsertShorturlPluginEditorInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit InsertShorturlPluginEditorInterfaceTest(QObject *parent = nullptr);
    ~InsertShorturlPluginEditorInterfaceTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif
