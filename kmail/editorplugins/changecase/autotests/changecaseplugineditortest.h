/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ChangeCasePLUGINEDITORTEST_H
#define ChangeCasePLUGINEDITORTEST_H

#include <QObject>

class ChangeCasePluginEditorTest : public QObject
{
    Q_OBJECT
public:
    explicit ChangeCasePluginEditorTest(QObject *parent = nullptr);
    ~ChangeCasePluginEditorTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif
