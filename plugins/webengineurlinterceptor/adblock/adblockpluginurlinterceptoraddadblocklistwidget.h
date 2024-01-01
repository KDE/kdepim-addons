/*
   SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

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
    struct LIBADBLOCKPLUGIN_TESTS_EXPORT AdBlockListInfo {
        QString name;
        QString url;
        [[nodiscard]] bool isValid() const;
    };

    explicit AdblockPluginUrlInterceptorAddAdblockListWidget(QWidget *parent = nullptr);
    ~AdblockPluginUrlInterceptorAddAdblockListWidget() override;

    [[nodiscard]] AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo info() const;
    void setInfo(const AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo &adblockInfo);

private:
    QLineEdit *const mName;
    QLineEdit *const mUrl;
};
LIBADBLOCKPLUGIN_TESTS_EXPORT QDebug operator<<(QDebug d, const AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo &t);
