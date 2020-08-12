/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef InsertSpecialCharacterPLUGINEDITORINTERFACETEST_H
#define InsertSpecialCharacterPLUGINEDITORINTERFACETEST_H

#include <QObject>

class InsertSpecialCharacterPluginEditorInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit InsertSpecialCharacterPluginEditorInterfaceTest(QObject *parent = nullptr);
    ~InsertSpecialCharacterPluginEditorInterfaceTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif
