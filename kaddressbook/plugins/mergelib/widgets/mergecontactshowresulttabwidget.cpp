/*
   SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactshowresulttabwidget.h"
#include <KContacts/Addressee>
#include "widgets/mergecontactinfowidget.h"

#include <QTabBar>
#include "kaddressbookmergelibprivate_debug.h"

using namespace KABMergeContacts;

MergeContactShowResultTabWidget::MergeContactShowResultTabWidget(QWidget *parent)
    : QTabWidget(parent)
{
    updateTabWidget();
}

MergeContactShowResultTabWidget::~MergeContactShowResultTabWidget()
{
}

void MergeContactShowResultTabWidget::updateTabWidget()
{
    tabBar()->setVisible(count() > 1);
}

bool MergeContactShowResultTabWidget::tabBarVisible() const
{
    return tabBar()->isVisible();
}

void MergeContactShowResultTabWidget::showMergedContacts(const Akonadi::Item::List &lstItem)
{
    clear();
    for (const Akonadi::Item &item : lstItem) {
        addMergedContact(item, false);
    }
    updateTabWidget();
}

void MergeContactShowResultTabWidget::addMergedContact(const Akonadi::Item &item, bool updateTab)
{
    if (item.hasPayload<KContacts::Addressee>()) {
        const KContacts::Addressee address = item.payload<KContacts::Addressee>();
        MergeContactInfoWidget *infoWidget = new MergeContactInfoWidget;
        infoWidget->setContact(item);
        addTab(infoWidget, address.name());
        if (updateTab) {
            updateTabWidget();
        }
    } else {
        qCDebug(KADDRESSBOOKMERGELIBPRIVATE_LOG) << " don't have address";
    }
}
