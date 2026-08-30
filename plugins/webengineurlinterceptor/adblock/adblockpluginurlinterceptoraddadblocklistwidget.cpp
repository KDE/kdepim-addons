/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockpluginurlinterceptoraddadblocklistwidget.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
using namespace Qt::Literals::StringLiterals;

AdblockPluginUrlInterceptorAddAdblockListWidget::AdblockPluginUrlInterceptorAddAdblockListWidget(QWidget *parent)
    : QWidget{parent}
    , mName(new QLineEdit(this))
    , mUrl(new QLineEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName("mainLayout"_L1);

    mName->setObjectName("mName"_L1);
    mUrl->setObjectName("mUrl"_L1);

    mName->setClearButtonEnabled(true);
    mUrl->setClearButtonEnabled(true);
    KLineEditEventHandler::catchReturnKey(mName);
    KLineEditEventHandler::catchReturnKey(mUrl);

    mainLayout->addRow(i18n("Name:"), mName);
    mainLayout->addRow(i18n("Url:"), mUrl);
    mName->setFocus();
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

bool AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo::isValid() const
{
    return !name.trimmed().isEmpty() && !url.trimmed().isEmpty();
}

bool AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo::operator==(const AdBlockListInfo &other) const
{
    return name == other.name && url == other.url;
}

bool AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo::operator!=(const AdBlockListInfo &other) const
{
    return !AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo::operator==(other);
}

QDebug operator<<(QDebug d, const AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo &t)
{
    d << " Name " << t.name;
    d << " Url " << t.url;
    return d;
}

#include "moc_adblockpluginurlinterceptoraddadblocklistwidget.cpp"
