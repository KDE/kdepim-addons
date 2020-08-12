/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ADBLOCKPLUGINURLINTERCEPTORTEST_H
#define ADBLOCKPLUGINURLINTERCEPTORTEST_H

#include <QObject>

class AdblockPluginUrlInterceptorTest : public QObject
{
    Q_OBJECT
public:
    explicit AdblockPluginUrlInterceptorTest(QObject *parent = nullptr);
    ~AdblockPluginUrlInterceptorTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // ADBLOCKPLUGINURLINTERCEPTORTEST_H
