/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "adblockplugin_private_export.h"
#include <QWidget>
class QLineEdit;
class LIBADBLOCKPLUGIN_TESTS_EXPORT AdblockPluginUrlInterceptorAddAdblockListWidget : public QWidget
{
    Q_OBJECT
public:
    struct AdBlockListInfo {
        QString name;
        QString url;
    };

    explicit AdblockPluginUrlInterceptorAddAdblockListWidget(QWidget *parent = nullptr);
    ~AdblockPluginUrlInterceptorAddAdblockListWidget() override;

    Q_REQUIRED_RESULT AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo info() const;
    void setInfo(const AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo &adblockInfo);

private:
    QLineEdit *const mName;
    QLineEdit *const mUrl;
};
