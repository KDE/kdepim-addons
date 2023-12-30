/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfiltertreeview.h"
#include "adblockfilter.h"
#include "adblockfilterlistsmodel.h"
#include "adblockmanager.h"
#include "adblockpluginurlinterceptoraddadblocklistdialog.h"
#include "globalsettings_webengineurlinterceptoradblock.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QContextMenuEvent>
#include <QHeaderView>
#include <QMenu>
#include <QPointer>
#include <QSortFilterProxyModel>

AdblockFilterTreeView::AdblockFilterTreeView(QWidget *parent)
    : QTreeView(parent)
    , mAdblockFilterListsModel(new AdblockFilterListsModel(this))
    , mSortFilterProxyModel(new QSortFilterProxyModel(this))
{
    mAdblockFilterListsModel->setObjectName(QLatin1StringView("mAdblockFilterListsModel"));

    mSortFilterProxyModel->setObjectName(QLatin1StringView("mSortFilterProxyModel"));

    mSortFilterProxyModel->setSourceModel(mAdblockFilterListsModel);
    setModel(mSortFilterProxyModel);
    setContextMenuPolicy(Qt::DefaultContextMenu);

    for (int c = 0; c < header()->count(); ++c) {
        header()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
    setRootIsDecorated(false);
    setSortingEnabled(true);
}

AdblockFilterTreeView::~AdblockFilterTreeView() = default;

void AdblockFilterTreeView::setFilterString(const QString &str)
{
    mSortFilterProxyModel->setFilterFixedString(str);
}

void AdblockFilterTreeView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;

    const QModelIndexList itemSelected = selectionModel()->selectedRows();

    auto addAction = new QAction(QIcon::fromTheme(QStringLiteral("list-add")), i18n("Add..."), &menu);
    connect(addAction, &QAction::triggered, this, &AdblockFilterTreeView::slotAddAdblock);
    menu.addAction(addAction);

    const int selectedItemsNumber = itemSelected.count();
    // qDebug() <<" selectedItemsNumber " << selectedItemsNumber;
    if (selectedItemsNumber == 1) { // Edit only one element
        auto modifyAction = new QAction(QIcon::fromTheme(QStringLiteral("list-add")), i18n("Modify..."), &menu);
        connect(modifyAction, &QAction::triggered, this, [this, itemSelected]() {
            slotModifyAdblock(itemSelected.at(0));
        });
        menu.addAction(modifyAction);
    }

    if (selectedItemsNumber >= 1) { // Remove multi elements
        menu.addSeparator();
        auto deleteAction = new QAction(QIcon::fromTheme(QStringLiteral("edit-delete")), i18n("Delete"), &menu);
        connect(deleteAction, &QAction::triggered, this, &AdblockFilterTreeView::slotDeleteAdblock);
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

void AdblockFilterTreeView::slotAddAdblock()
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

void AdblockFilterTreeView::slotModifyAdblock(const QModelIndex &index)
{
    QPointer<AdblockPluginUrlInterceptorAddAdblockListDialog> dlg = new AdblockPluginUrlInterceptorAddAdblockListDialog(this);
    AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo info;
    const QModelIndex newModelIndex = mSortFilterProxyModel->mapToSource(index);

    const QModelIndex modelIndexUrl = mAdblockFilterListsModel->index(newModelIndex.row(), AdblockFilterListsModel::UrlRole);
    const QModelIndex modelIndexName = mAdblockFilterListsModel->index(newModelIndex.row(), AdblockFilterListsModel::NameRole);
    // qDebug() << " modelIndexUrl " << modelIndexUrl.data() << " modelIndexName " << modelIndexName.data();
    info.name = modelIndexName.data().toString();
    info.url = modelIndexUrl.data().toString();
    dlg->setInfo(info);
    if (dlg->exec()) {
        const AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo info = dlg->info();
        if (info.isValid()) {
            // TODO
        }
    }
    delete dlg;
}

void AdblockFilterTreeView::slotDeleteAdblock()
{
    if (KMessageBox::questionTwoActions(this, i18n("Remove"), i18nc("@title:window", "Remove"), KStandardGuiItem::ok(), KStandardGuiItem::cancel())
        == KMessageBox::ButtonCode::PrimaryAction) {
        // mAdblockFilterListsModel->removeList();
        // TODO
    }
}

void AdblockFilterTreeView::loadSettings()
{
    mAdblockFilterListsModel->setAdblockFilter(AdblockManager::self()->adblockFilterLists());
}

void AdblockFilterTreeView::saveSettings() const
{
    AdblockManager::self()->setAdblockFilterLists(mAdblockFilterListsModel->adblockFilter());
    AdblockManager::self()->saveSettings();
}

#include "moc_adblockfiltertreeview.cpp"
