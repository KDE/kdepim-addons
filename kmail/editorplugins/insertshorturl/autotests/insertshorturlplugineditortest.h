/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef InsertShorturlPLUGINEDITORTEST_H
#define InsertShorturlPLUGINEDITORTEST_H

#include <QObject>

class InsertShorturlPluginEditorTest : public QObject
{
    Q_OBJECT
public:
    explicit InsertShorturlPluginEditorTest(QObject *parent = nullptr);
    ~InsertShorturlPluginEditorTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif
