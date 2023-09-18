/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockpluginurlinterceptoraddadblocklistwidget.h"
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>

AdblockPluginUrlInterceptorAddAdblockListWidget::AdblockPluginUrlInterceptorAddAdblockListWidget(QWidget *parent)
    : QWidget{parent}
    , mName(new QLineEdit(this))
    , mUrl(new QLineEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mName->setObjectName(QStringLiteral("mName"));
    mUrl->setObjectName(QStringLiteral("mUrl"));

    mName->setClearButtonEnabled(true);
    mUrl->setClearButtonEnabled(true);

    mainLayout->addRow(i18n("Name:"), mName);
    mainLayout->addRow(i18n("Url:"), mUrl);
}

AdblockPluginUrlInterceptorAddAdblockListWidget::~AdblockPluginUrlInterceptorAddAdblockListWidget() = default;

AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo AdblockPluginUrlInterceptorAddAdblockListWidget::info() const
{
    AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo i;
    i.name = mName->text();
    i.url = mUrl->text();
    return i;
}

void AdblockPluginUrlInterceptorAddAdblockListWidget::setInfo(const AdBlockListInfo &adblockInfo)
{
    mName->setText(adblockInfo.name);
    mUrl->setText(adblockInfo.url);
}

#include "moc_adblockpluginurlinterceptoraddadblocklistwidget.cpp"
