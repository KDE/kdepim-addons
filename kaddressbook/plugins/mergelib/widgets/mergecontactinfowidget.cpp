/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mergecontactinfowidget.h"

#include <Akonadi/GrantleeContactViewer>

#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>
using namespace Qt::Literals::StringLiterals;

using namespace KABMergeContacts;

MergeContactInfoWidget::MergeContactInfoWidget(QWidget *parent)
    : QWidget(parent)
    , mStackWidget(new QStackedWidget(this))
    , mNoContactSelected(new QLabel(this))
    , mContactViewer(new KAddressBookGrantlee::GrantleeContactViewer(this))
{
    auto lay = new QHBoxLayout(this);
    mStackWidget->setObjectName("stackedwidget"_L1);

    mContactViewer->setObjectName("contactwidget"_L1);
    mContactViewer->setForceDisableQRCode(true);

    mStackWidget->addWidget(mContactViewer);

    mNoContactSelected->setObjectName("nocontact"_L1);
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
