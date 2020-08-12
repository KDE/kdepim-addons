/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef InsertEmailPLUGINEDITORTEST_H
#define InsertEmailPLUGINEDITORTEST_H

#include <QObject>

class InsertEmailPluginEditorTest : public QObject
{
    Q_OBJECT
public:
    explicit InsertEmailPluginEditorTest(QObject *parent = nullptr);
    ~InsertEmailPluginEditorTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif
