/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef AutoCorrectionPLUGINEDITORTEST_H
#define AutoCorrectionPLUGINEDITORTEST_H

#include <QObject>

class AutoCorrectionPluginEditorTest : public QObject
{
    Q_OBJECT
public:
    explicit AutoCorrectionPluginEditorTest(QObject *parent = nullptr);
    ~AutoCorrectionPluginEditorTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif
