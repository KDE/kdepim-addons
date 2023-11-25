/*
   SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>

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
    , mStackWidget(new QStackedWidget(this))
    , mNoContactSelected(new QLabel(this))
    , mContactViewer(new KAddressBookGrantlee::GrantleeContactViewer(this))
{
    auto lay = new QHBoxLayout(this);
    mStackWidget->setObjectName(QLatin1StringView("stackedwidget"));

    mContactViewer->setObjectName(QLatin1StringView("contactwidget"));
    mContactViewer->setForceDisableQRCode(true);

    mStackWidget->addWidget(mContactViewer);

    mNoContactSelected->setObjectName(QLatin1StringView("nocontact"));
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

#include "moc_mergecontactinfowidget.cpp"
