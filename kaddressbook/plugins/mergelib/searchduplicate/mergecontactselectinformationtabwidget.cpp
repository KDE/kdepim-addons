/*
    SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "mergecontactselectinformationtabwidget.h"
#include "widgets/mergecontactselectinformationscrollarea.h"
#include <KLocalizedString>
#include <QTabBar>

using namespace KABMergeContacts;

MergeContactSelectInformationTabWidget::MergeContactSelectInformationTabWidget(QWidget *parent)
    : QTabWidget(parent)
{
}

MergeContactSelectInformationTabWidget::~MergeContactSelectInformationTabWidget() = default;

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
    auto area = new KABMergeContacts::MergeContactSelectInformationScrollArea;
    area->setContacts(list.conflictInformation, list.list, col);
    addTab(area, i18n("Duplicate contact %1", count() + 1));
}

void MergeContactSelectInformationTabWidget::setRequiresSelectInformationWidgets(const QList<KABMergeContacts::MergeConflictResult> &list,
                                                                                 const Akonadi::Collection &col)
{
    clear();
    for (const KABMergeContacts::MergeConflictResult &lst : list) {
        addNewWidget(lst, col);
    }
    updateTabWidget();
}

#include "moc_mergecontactselectinformationtabwidget.cpp"
