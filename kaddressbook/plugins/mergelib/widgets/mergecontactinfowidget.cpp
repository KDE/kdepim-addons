/*
   SPDX-FileCopyrightText: 2014-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mergecontactinfowidget.h"

#include <Akonadi/GrantleeContactViewer>

#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>

using namespace KABMergeContacts;

MergeContactInfoWidget::MergeContactInfoWidget(QWidget *parent)
    : QWidget(parent)
{
    auto lay = new QHBoxLayout(this);
    mStackWidget = new QStackedWidget;
    mStackWidget->setObjectName(QStringLiteral("stackedwidget"));

    mContactViewer = new KAddressBookGrantlee::GrantleeContactViewer;
    mContactViewer->setObjectName(QStringLiteral("contactwidget"));
    mContactViewer->setForceDisableQRCode(true);

    mStackWidget->addWidget(mContactViewer);

    mNoContactSelected = new QLabel;
    mNoContactSelected->setObjectName(QStringLiteral("nocontact"));
    mStackWidget->addWidget(mNoContactSelected);

    lay->addWidget(mStackWidget);
    mStackWidget->setCurrentWidget(mNoContactSelected);
}

MergeContactInfoWidget::~MergeContactInfoWidget() = default;

void MergeContactInfoWidget::setContact(const Akonadi::Item &item)
{
    if (item.isValid()) {
        mContactViewer->setContact(item);
        mStackWidget->setCurrentWidget(mContactViewer);
    } else {
        mStackWidget->setCurrentWidget(mNoContactSelected);
    }
}
