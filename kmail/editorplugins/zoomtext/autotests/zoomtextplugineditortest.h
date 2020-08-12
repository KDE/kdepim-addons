/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ZoomTextPLUGINEDITORTEST_H
#define ZoomTextPLUGINEDITORTEST_H

#include <QObject>

class ZoomTextPluginEditorTest : public QObject
{
    Q_OBJECT
public:
    explicit ZoomTextPluginEditorTest(QObject *parent = nullptr);
    ~ZoomTextPluginEditorTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif
