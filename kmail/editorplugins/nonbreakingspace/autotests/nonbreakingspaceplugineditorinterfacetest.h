/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef NonBreakingSpacePLUGINEDITORINTERFACETEST_H
#define NonBreakingSpacePLUGINEDITORINTERFACETEST_H

#include <QObject>

class NonBreakingSpacePluginEditorInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit NonBreakingSpacePluginEditorInterfaceTest(QObject *parent = nullptr);
    ~NonBreakingSpacePluginEditorInterfaceTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif
