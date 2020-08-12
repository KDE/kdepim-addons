/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef InsertSpecialCharacterPLUGINEDITORTEST_H
#define InsertSpecialCharacterPLUGINEDITORTEST_H

#include <QObject>

class InsertSpecialCharacterPluginEditorTest : public QObject
{
    Q_OBJECT
public:
    explicit InsertSpecialCharacterPluginEditorTest(QObject *parent = nullptr);
    ~InsertSpecialCharacterPluginEditorTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif
