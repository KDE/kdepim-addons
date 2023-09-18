/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockpluginurlinterceptoraddadblocklistdialog.h"
#include "adblockpluginurlinterceptoraddadblocklistwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

AdblockPluginUrlInterceptorAddAdblockListDialog::AdblockPluginUrlInterceptorAddAdblockListDialog(QWidget *parent)
    : QDialog(parent)
    , mAddAdblockListWidget(new AdblockPluginUrlInterceptorAddAdblockListWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Add Adblock List"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mAddAdblockListWidget->setObjectName(QStringLiteral("mAddAdblockListWidget"));
    mainLayout->addWidget(mAddAdblockListWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AdblockPluginUrlInterceptorAddAdblockListDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AdblockPluginUrlInterceptorAddAdblockListDialog::reject);
}

AdblockPluginUrlInterceptorAddAdblockListDialog::~AdblockPluginUrlInterceptorAddAdblockListDialog() = default;

AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo AdblockPluginUrlInterceptorAddAdblockListDialog::info() const
{
    return mAddAdblockListWidget->info();
}

void AdblockPluginUrlInterceptorAddAdblockListDialog::setInfo(const AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo &adblockInfo)
{
    mAddAdblockListWidget->setInfo(adblockInfo);
}

#include "moc_adblockpluginurlinterceptoraddadblocklistdialog.cpp"
