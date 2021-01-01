/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef ChangeCasePLUGINEDITORINTERFACETEST_H
#define ChangeCasePLUGINEDITORINTERFACETEST_H

#include <QObject>

class ChangeCasePluginEditorInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit ChangeCasePluginEditorInterfaceTest(QObject *parent = nullptr);
    ~ChangeCasePluginEditorInterfaceTest();
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif
