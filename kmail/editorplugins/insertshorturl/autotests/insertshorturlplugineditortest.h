/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

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
    ~InsertShorturlPluginEditorTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif
