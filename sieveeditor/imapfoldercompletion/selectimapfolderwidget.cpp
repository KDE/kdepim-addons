/*
   Copyright (C) 2016-2020 Laurent Montel <montel@kde.org>
   based on subscriptiondialog from kdepim-runtime

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "selectimapfolderwidget.h"
#include "selectimaploadfoldersjob.h"
#include "selectimapfoldertreeview.h"
#include "selectimapfoldermodel.h"
#include "imapfoldercompletionplugin_debug.h"
#include <KMessageBox>
#include <QTreeView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QLineEdit>
#include <QInputDialog>
#include <QSortFilterProxyModel>
#include <QVBoxLayout>

#include <KLocalizedString>
#include <QToolButton>

SelectImapFolderWidget::SelectImapFolderWidget(const KSieveUi::SieveImapAccountSettings &account, QWidget *parent)
    : QWidget(parent)
    , mAccount(account)
{
    bool modelIsInitialized = false;
    mModel = SelectImapFolderModel::self()->folderModel(mAccount, modelIsInitialized);
    connect(SelectImapFolderModel::self(), &SelectImapFolderModel::modelLoaded, this, &SelectImapFolderWidget::slotModelLoaded);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(topLayout);
    mSearchLineEdit = new QLineEdit(this);
    mSearchLineEdit->setObjectName(QStringLiteral("searchline"));
    mSearchLineEdit->setClearButtonEnabled(true);
    mSearchLineEdit->setPlaceholderText(i18n("Search..."));
    topLayout->addWidget(mSearchLineEdit);

    QToolButton *refreshImap = new QToolButton(this);
    refreshImap->setObjectName(QStringLiteral("refreshimap"));
    refreshImap->setIcon(QIcon::fromTheme(QStringLiteral("view-refresh")));
    refreshImap->setToolTip(i18n("Refresh IMAP Folder List"));
    connect(refreshImap, &QToolButton::clicked, this, &SelectImapFolderWidget::slotRefreshImap);
    topLayout->addWidget(refreshImap);

    mTreeView = new SelectImapFolderTreeView(this);
    mTreeView->setObjectName(QStringLiteral("treeview"));
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

SelectImapFolderWidget::~SelectImapFolderWidget()
{
}

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
            //TODO more check for folder name ?
            SelectImapFolderModel::self()->createNewFolder(mAccount, currentPath + QLatin1Char('/') + name);
        } else {
            KMessageBox::error(this, i18n("Empty folder name is not supported."), i18n("Create Folder"));
        }
    }
}

void SelectImapFolderWidget::slotCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    Q_EMIT folderIsSelected(current.isValid());
}

void SelectImapFolderWidget::slotRefreshImap()
{
    SelectImapFolderModel::self()->reloadFolderModel(mAccount);
}
