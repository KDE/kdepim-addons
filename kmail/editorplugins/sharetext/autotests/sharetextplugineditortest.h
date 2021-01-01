/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ShareTextPLUGINEDITORTEST_H
#define ShareTextPLUGINEDITORTEST_H

#include <QObject>

class ShareTextPluginEditorTest : public QObject
{
    Q_OBJECT
public:
    explicit ShareTextPluginEditorTest(QObject *parent = nullptr);
    ~ShareTextPluginEditorTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif
