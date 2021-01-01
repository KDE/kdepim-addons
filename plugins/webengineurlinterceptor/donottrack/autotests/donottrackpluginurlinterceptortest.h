/*
    SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DONOTTRACKPLUGINURLINTERCEPTORTEST_H
#define DONOTTRACKPLUGINURLINTERCEPTORTEST_H

#include <QObject>

class DoNotTrackPluginUrlInterceptorTest : public QObject
{
    Q_OBJECT
public:
    explicit DoNotTrackPluginUrlInterceptorTest(QObject *parent = nullptr);
    ~DoNotTrackPluginUrlInterceptorTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // DONOTTRACKPLUGINURLINTERCEPTORTEST_H
