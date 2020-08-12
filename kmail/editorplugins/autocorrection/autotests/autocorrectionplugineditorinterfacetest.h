/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef AutoCorrectionPLUGINEDITORINTERFACETEST_H
#define AutoCorrectionPLUGINEDITORINTERFACETEST_H

#include <QObject>

class AutoCorrectionPluginEditorInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit AutoCorrectionPluginEditorInterfaceTest(QObject *parent = nullptr);
    ~AutoCorrectionPluginEditorInterfaceTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif
