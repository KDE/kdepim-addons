/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ZoomTextPLUGINEDITORINTERFACETEST_H
#define ZoomTextPLUGINEDITORINTERFACETEST_H

#include <QObject>

class ZoomTextPluginEditorInterfaceTest : public QObject
{
    Q_OBJECT
public:
    explicit ZoomTextPluginEditorInterfaceTest(QObject *parent = nullptr);
    ~ZoomTextPluginEditorInterfaceTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif
