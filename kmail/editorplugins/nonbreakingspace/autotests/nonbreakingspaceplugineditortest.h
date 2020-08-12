/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef NonBreakingSpacePLUGINEDITORTEST_H
#define NonBreakingSpacePLUGINEDITORTEST_H

#include <QObject>

class NonBreakingSpacePluginEditorTest : public QObject
{
    Q_OBJECT
public:
    explicit NonBreakingSpacePluginEditorTest(QObject *parent = nullptr);
    ~NonBreakingSpacePluginEditorTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif
