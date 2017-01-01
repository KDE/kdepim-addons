/*
    Copyright (c) 2015-2017 Montel Laurent <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "mergecontactselectinformationtabwidget.h"
#include "widgets/mergecontactselectinformationscrollarea.h"
#include <QTabBar>
#include <KLocalizedString>

using namespace KABMergeContacts;

MergeContactSelectInformationTabWidget::MergeContactSelectInformationTabWidget(QWidget *parent)
    : QTabWidget(parent)
{

}

MergeContactSelectInformationTabWidget::~MergeContactSelectInformationTabWidget()
{

}

void MergeContactSelectInformationTabWidget::updateTabWidget()
{
    tabBar()->setVisible(count() > 1);
}

bool MergeContactSelectInformationTabWidget::tabBarVisible() const
{
    return tabBar()->isVisible();
}

void MergeContactSelectInformationTabWidget::addNewWidget(const KABMergeContacts::MergeConflictResult &list, const Akonadi::Collection &col)
{
    KABMergeContacts::MergeContactSelectInformationScrollArea *area = new KABMergeContacts::MergeContactSelectInformationScrollArea;
    area->setContacts(list.conflictInformation, list.list, col);
    addTab(area, i18n("Duplicate contact %1", count() + 1));
}

void MergeContactSelectInformationTabWidget::setRequiresSelectInformationWidgets(const QVector<KABMergeContacts::MergeConflictResult> &list, const Akonadi::Collection &col)
{
    clear();
    for (const KABMergeContacts::MergeConflictResult &lst : list) {
        addNewWidget(lst, col);
    }
    updateTabWidget();
}
