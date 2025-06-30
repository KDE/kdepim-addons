/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkfoldersizeaccountpluginwidget.h"
#include <Akonadi/ChangeRecorder>
#include <Akonadi/CollectionFilterProxyModel>
#include <Akonadi/EntityTreeModel>
#include <KLocalizedString>
#include <KMime/Message>
#include <QTreeView>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
CheckFolderSizeAccountPluginWidget::CheckFolderSizeAccountPluginWidget(QWidget *parent)
    : QWidget{parent}
    , mFolderView(new QTreeView(this))
    , mChangeRecorder(new Akonadi::ChangeRecorder(this))
    , mCollectionFilter(new QSortFilterProxyModel(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    // Create a new change recorder.
    mChangeRecorder->setMimeTypeMonitored(KMime::Message::mimeType());
    mChangeRecorder->fetchCollection(true);
    mChangeRecorder->setAllMonitored(true);

    mModel = new Akonadi::EntityTreeModel(mChangeRecorder, this);
    // Set the model to show only collections, not items.
    mModel->setItemPopulationStrategy(Akonadi::EntityTreeModel::NoItemPopulation);
    connect(mModel, &Akonadi::EntityTreeModel::collectionTreeFetched, this, &CheckFolderSizeAccountPluginWidget::slotCollectionTreeFetched);

    auto mimeTypeProxy = new Akonadi::CollectionFilterProxyModel(this);
    mimeTypeProxy->setExcludeVirtualCollections(true);
    mimeTypeProxy->addMimeTypeFilters(QStringList() << KMime::Message::mimeType());
    mimeTypeProxy->setSourceModel(mModel);

    // mNewMailNotifierProxyModel->setSourceModel(mimeTypeProxy);

    mCollectionFilter->setRecursiveFilteringEnabled(true);
    mCollectionFilter->setSourceModel(mimeTypeProxy);
    mCollectionFilter->setFilterCaseSensitivity(Qt::CaseInsensitive);
    mCollectionFilter->setSortRole(Qt::DisplayRole);
    mCollectionFilter->setSortCaseSensitivity(Qt::CaseSensitive);
    mCollectionFilter->setSortLocaleAware(true);

    // TODO a list of folder => show size (work only on imap and co)
    mFolderView->setObjectName(u"mFolderView"_s);
    mainLayout->addWidget(mFolderView);
}

CheckFolderSizeAccountPluginWidget::~CheckFolderSizeAccountPluginWidget() = default;

void CheckFolderSizeAccountPluginWidget::slotCollectionTreeFetched()
{
    mCollectionFilter->sort(0, Qt::AscendingOrder);
    mFolderView->expandAll();
}

#include "moc_checkfoldersizeaccountpluginwidget.cpp"
