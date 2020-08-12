/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ADBLOCKPLUGINURLINTERCEPTORCONFIGUREWIDGETTEST_H
#define ADBLOCKPLUGINURLINTERCEPTORCONFIGUREWIDGETTEST_H

#include <QObject>

class AdblockPluginUrlInterceptorConfigureWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit AdblockPluginUrlInterceptorConfigureWidgetTest(QObject *parent = nullptr);
    ~AdblockPluginUrlInterceptorConfigureWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // ADBLOCKPLUGINURLINTERCEPTORCONFIGUREWIDGETTEST_H
