/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfilterlistsview.h"
#include "adblockfilterlistsmodel.h"
#include "adblockmanager.h"
#include "adblockpluginurlinterceptoraddadblocklistdialog.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QContextMenuEvent>
#include <QMenu>
#include <QPointer>
#include <QSortFilterProxyModel>

AdblockFilterListsView::AdblockFilterListsView(QWidget *parent)
    : QListView(parent)
    , mAdblockFilterListsModel(new AdblockFilterListsModel(this))
    , mSortFilterProxyModel(new QSortFilterProxyModel(this))
{
    mAdblockFilterListsModel->setObjectName(QStringLiteral("mAdblockFilterListsModel"));

    mSortFilterProxyModel->setObjectName(QStringLiteral("mSortFilterProxyModel"));

    mAdblockFilterListsModel->setAdblockFilter(AdblockManager::self()->adblockFilterLists());
    mSortFilterProxyModel->setSourceModel(mAdblockFilterListsModel);
    setModel(mSortFilterProxyModel);
    setContextMenuPolicy(Qt::DefaultContextMenu);
}

AdblockFilterListsView::~AdblockFilterListsView() = default;

void AdblockFilterListsView::setFilterString(const QString &str)
{
    mSortFilterProxyModel->setFilterFixedString(str);
}

void AdblockFilterListsView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;

    const auto itemSelected = selectionModel()->selectedIndexes();

    auto addAction = new QAction(QIcon::fromTheme(QStringLiteral("list-add")), i18n("Add..."), &menu);
    connect(addAction, &QAction::triggered, this, &AdblockFilterListsView::slotAddAdblock);
    menu.addAction(addAction);

    if (itemSelected.count() > 0) {
        auto modifyAction = new QAction(QIcon::fromTheme(QStringLiteral("list-add")), i18n("Modify..."), &menu);
        connect(modifyAction, &QAction::triggered, this, &AdblockFilterListsView::slotModifyAdblock);
        menu.addAction(modifyAction);

        menu.addSeparator();
        auto deleteAction = new QAction(QIcon::fromTheme(QStringLiteral("edit-delete")), i18n("Delete"), &menu);
        connect(deleteAction, &QAction::triggered, this, &AdblockFilterListsView::slotDeleteAdblock);
        menu.addAction(deleteAction);
    }
    menu.exec(event->globalPos());
}

[[nodiscard]] AdblockFilter convertToAdblockFilter(const AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo &info)
{
    AdblockFilter filter;
    filter.setName(info.name);
    filter.setUrl(info.url);
    return filter;
}

void AdblockFilterListsView::slotAddAdblock()
{
    QPointer<AdblockPluginUrlInterceptorAddAdblockListDialog> dlg = new AdblockPluginUrlInterceptorAddAdblockListDialog(this);
    if (dlg->exec()) {
        const AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo info = dlg->info();
        if (info.isValid()) {
            mAdblockFilterListsModel->insertList(std::move(convertToAdblockFilter(info)));
        }
    }
    delete dlg;
}

void AdblockFilterListsView::slotModifyAdblock()
{
    QPointer<AdblockPluginUrlInterceptorAddAdblockListDialog> dlg = new AdblockPluginUrlInterceptorAddAdblockListDialog(this);
    // TODO dlg->setInfo(...)
    if (dlg->exec()) {
        const AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo info = dlg->info();
        if (info.isValid()) {
            // TODO
        }
    }
    delete dlg;
}

void AdblockFilterListsView::slotDeleteAdblock()
{
    if (KMessageBox::questionTwoActions(this, i18n("Remove"), i18nc("@title:window", "Remove"), KStandardGuiItem::ok(), KStandardGuiItem::cancel())
        == KMessageBox::ButtonCode::PrimaryAction) {
        // mAdblockFilterListsModel->removeList();
        // TODO
    }
}

#include "moc_adblockfilterlistsview.cpp"
