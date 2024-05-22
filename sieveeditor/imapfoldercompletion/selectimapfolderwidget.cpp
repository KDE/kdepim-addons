/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>
   based on subscriptiondialog from kdepim-runtime

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimapfolderwidget.h"
#include "imapfoldercompletionplugin_debug.h"
#include "selectimapfoldermodel.h"
#include "selectimapfoldertreeview.h"
#include "selectimaploadfoldersjob.h"
#include <KMessageBox>
#include <QHeaderView>
#include <QInputDialog>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QVBoxLayout>

#include <KLocalizedString>
#include <QToolButton>

SelectImapFolderWidget::SelectImapFolderWidget(const KSieveCore::SieveImapAccountSettings &account, QWidget *parent)
    : QWidget(parent)
    , mAccount(account)
    , mSearchLineEdit(new QLineEdit(this))
    , mTreeView(new SelectImapFolderTreeView(this))
{
    bool modelIsInitialized = false;
    mModel = SelectImapFolderModel::self()->folderModel(mAccount, modelIsInitialized);
    connect(SelectImapFolderModel::self(), &SelectImapFolderModel::modelLoaded, this, &SelectImapFolderWidget::slotModelLoaded);
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));
    mainLayout->setContentsMargins({});

    auto topLayout = new QHBoxLayout;
    topLayout->setContentsMargins({});
    mainLayout->addLayout(topLayout);
    mSearchLineEdit->setObjectName(QLatin1StringView("searchline"));
    mSearchLineEdit->setClearButtonEnabled(true);
    mSearchLineEdit->setPlaceholderText(i18n("Search…"));
    topLayout->addWidget(mSearchLineEdit);

    auto refreshImap = new QToolButton(this);
    refreshImap->setObjectName(QLatin1StringView("refreshimap"));
    refreshImap->setIcon(QIcon::fromTheme(QStringLiteral("view-refresh")));
    refreshImap->setToolTip(i18nc("@info:tooltip", "Refresh IMAP Folder List"));
    connect(refreshImap, &QToolButton::clicked, this, &SelectImapFolderWidget::slotRefreshImap);
    topLayout->addWidget(refreshImap);

    mTreeView->setObjectName(QLatin1StringView("treeview"));
    mTreeView->header()->hide();
    mFilter = new QSortFilterProxyModel(this);
    mFilter->setFilterCaseSensitivity(Qt::CaseInsensitive);
    mFilter->setRecursiveFilteringEnabled(true);
    mFilter->setSourceModel(mModel);

    mTreeView->setModel(mFilter);
    connect(mTreeView, &QTreeView::doubleClicked, this, &SelectImapFolderWidget::slotDoubleClicked);
    mainLayout->addWidget(mTreeView);

    connect(mSearchLineEdit, &QLineEdit::textChanged, this, &SelectImapFolderWidget::slotSearchPattern);
    connect(mTreeView->selectionModel(), &QItemSelectionModel::currentChanged, this, &SelectImapFolderWidget::slotCurrentChanged);
    if (modelIsInitialized) {
        mTreeView->setStatus(SelectImapFolderTreeView::Success);
    }
}

SelectImapFolderWidget::~SelectImapFolderWidget() = default;

void SelectImapFolderWidget::slotModelLoaded(QStandardItemModel *model, bool success)
{
    if (mModel == model) {
        mTreeView->setStatus(success ? SelectImapFolderTreeView::Success : SelectImapFolderTreeView::Failed);
    }
}

void SelectImapFolderWidget::slotSearchPattern(const QString &pattern)
{
    mTreeView->expandAll();
    mFilter->setFilterFixedString(pattern);
}

void SelectImapFolderWidget::slotDoubleClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        Q_EMIT folderSelected();
    }
}

QString SelectImapFolderWidget::selectedFolderName() const
{
    QString currentPath;
    const QModelIndex index = mTreeView->currentIndex();
    if (index.isValid()) {
        currentPath = index.data(SelectImapLoadFoldersJob::PathRole).toString();
    }
    return currentPath;
}

void SelectImapFolderWidget::createFolder()
{
    const QModelIndex index = mTreeView->currentIndex();
    if (index.isValid()) {
        bool ok = false;
        const QString name = QInputDialog::getText(this, i18n("Create Folder"), i18n("Folder Name:"), {}, {}, &ok);
        if (!ok) {
            return;
        }
        if (!name.trimmed().isEmpty()) {
            const QString currentPath = index.data(SelectImapLoadFoldersJob::PathRole).toString();
            if (name.contains(QLatin1Char('/'))) {
                KMessageBox::error(this, i18n("Slashes are not allowed in folder names."), i18n("Create Folder"));
                return;
            }
            // TODO more check for folder name ?
            SelectImapFolderModel::self()->createNewFolder(mAccount, currentPath + QLatin1Char('/') + name);
        } else {
            KMessageBox::error(this, i18n("Empty folder name is not supported."), i18nc("@title:window", "Create Folder"));
        }
    }
}

void SelectImapFolderWidget::slotCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous)
    Q_EMIT folderIsSelected(current.isValid());
}

void SelectImapFolderWidget::slotRefreshImap()
{
    SelectImapFolderModel::self()->reloadFolderModel(mAccount);
}

#include "moc_selectimapfolderwidget.cpp"
