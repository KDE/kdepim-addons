/*
  SPDX-FileCopyrightText: 2010 Volker Krause <vkrause@kde.org>
  SPDX-FileCopyrightText: 2016 Sandro Knauß <sknauss@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QObject>

class RenderTest : public QObject
{
    Q_OBJECT

public Q_SLOTS:
    void initTestCase();

private Q_SLOTS:
    void testRender_data();
    void testRender();
    void testRenderKeyDetails_data();
    void testRenderKeyDetails();
};

