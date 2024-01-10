/*
   SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockfiltertreeview.h"
#include "adblockfilter.h"
#include "adblockfilterlistsmodel.h"
#include "adblockmanager.h"
#include "adblockpluginurlinterceptoraddadblocklistdialog.h"
#include "adblockviewfilterdialog.h"
#include "libadblockplugin_debug.h"
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

    for (int c = 0, total = header()->count(); c < total; ++c) {
        header()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
    setRootIsDecorated(false);
    setSortingEnabled(true);

    connect(AdblockManager::self(), &AdblockManager::refreshFinished, this, [this]() {
        loadSettings();
    });
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
        auto modifyAction = new QAction(QIcon::fromTheme(QStringLiteral("edit-rename")), i18n("Modify..."), &menu);
        connect(modifyAction, &QAction::triggered, this, [this, itemSelected]() {
            slotModifyAdblock(itemSelected.at(0));
        });
        menu.addAction(modifyAction);
        menu.addSeparator();
        auto deleteAction = new QAction(QIcon::fromTheme(QStringLiteral("edit-delete")), i18n("Delete"), &menu);
        connect(deleteAction, &QAction::triggered, this, [this, itemSelected]() {
            // For the moment remove only one element
            slotDeleteAdblock(itemSelected.at(0));
        });
        menu.addAction(deleteAction);

        menu.addSeparator();
        auto showAdblockAction = new QAction(QIcon::fromTheme(QStringLiteral("document-preview")), i18n("Show"), &menu);
        connect(showAdblockAction, &QAction::triggered, this, [this, itemSelected]() {
            const QModelIndex modelIndexUrl = mAdblockFilterListsModel->index(itemSelected.at(0).row(), AdblockFilterListsModel::Url);
            const QString filterText = AdblockManager::self()->adblockListText(modelIndexUrl.data().toString());
            if (filterText.isEmpty()) {
                AdblockViewFilterDialog dlg(this);
                dlg.setFilterText(filterText);
                dlg.exec();
            } else {
                qCWarning(LIBADBLOCKPLUGIN_PLUGIN_LOG) << "List is empty. Perhaps we need to refresh lists";
            }
        });
        menu.addAction(showAdblockAction);
    }
    menu.addSeparator();
    auto updateListsAction = new QAction(QIcon::fromTheme(QStringLiteral("view-refresh")), i18n("Update Lists"), &menu);
    connect(updateListsAction, &QAction::triggered, this, []() {
        AdblockManager::self()->refreshLists();
    });
    menu.addAction(updateListsAction);

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
            if (mAdblockFilterListsModel->insertList(std::move(convertToAdblockFilter(info)))) {
                mSettingsChanged = true;
            }
        }
    }
    delete dlg;
}

void AdblockFilterTreeView::slotModifyAdblock(const QModelIndex &index)
{
    QPointer<AdblockPluginUrlInterceptorAddAdblockListDialog> dlg = new AdblockPluginUrlInterceptorAddAdblockListDialog(this);
    AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo originalInfo;
    const QModelIndex newModelIndex = mSortFilterProxyModel->mapToSource(index);

    const QModelIndex modelIndexUrl = mAdblockFilterListsModel->index(newModelIndex.row(), AdblockFilterListsModel::Url);
    const QModelIndex modelIndexName = mAdblockFilterListsModel->index(newModelIndex.row(), AdblockFilterListsModel::Name);
    const QString listName = modelIndexName.data().toString();
    // qDebug() << " modelIndexUrl " << modelIndexUrl.data() << " modelIndexName " << modelIndexName.data();
    originalInfo.name = listName;
    originalInfo.url = modelIndexUrl.data().toString();
    dlg->setInfo(originalInfo);
    if (dlg->exec()) {
        const AdblockPluginUrlInterceptorAddAdblockListWidget::AdBlockListInfo info = dlg->info();
        if (info != originalInfo) {
            if (info.isValid()) {
                mAdblockFilterListsModel->removeList(listName);
                (void)mAdblockFilterListsModel->insertList(std::move(convertToAdblockFilter(info)));
                mSettingsChanged = true;
            }
        }
    }
    delete dlg;
}

void AdblockFilterTreeView::slotDeleteAdblock(const QModelIndex &index)
{
    const QModelIndex newModelIndex = mSortFilterProxyModel->mapToSource(index);
    const QModelIndex modelIndexName = mAdblockFilterListsModel->index(newModelIndex.row(), AdblockFilterListsModel::Name);
    const QString listName = modelIndexName.data().toString();
    if (KMessageBox::questionTwoActions(this,
                                        i18n("Do you want to remove \'%1\' ?", listName),
                                        i18nc("@title:window", "Remove List"),
                                        KStandardGuiItem::ok(),
                                        KStandardGuiItem::cancel())
        == KMessageBox::ButtonCode::PrimaryAction) {
        mAdblockFilterListsModel->removeList(listName);
        mSettingsChanged = true;
    }
}

void AdblockFilterTreeView::loadSettings()
{
    mAdblockFilterListsModel->setAdblockFilter(AdblockManager::self()->adblockFilterLists());
}

void AdblockFilterTreeView::saveSettings()
{
    if (mSettingsChanged) {
        AdblockManager::self()->setAdblockFilterLists(mAdblockFilterListsModel->adblockFilter());
        Q_EMIT settingsChanged();
    }
}

#include "moc_adblockfiltertreeview.cpp"
