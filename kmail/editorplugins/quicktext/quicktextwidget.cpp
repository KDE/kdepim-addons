/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

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

#include "quicktextwidget.h"
#include "quicktextmanager.h"

#include <kactioncollection.h>
#include <KLocalizedString>
#include <KMessageBox>

#include <QContextMenuEvent>
#include <QHeaderView>
#include <QMenu>
#include <MailCommon/SnippetsModel>

QuicktextWidget::QuicktextWidget(QWidget *parent)
    : QTreeView(parent)
{
    header()->hide();
    setAcceptDrops(true);
    setDragEnabled(true);
    setRootIsDecorated(true);
    setAlternatingRowColors(true);
    mSnippetsManager = new QuicktextManager(this, this);
    connect(mSnippetsManager, &QuicktextManager::insertPlainText, this, &QuicktextWidget::insertSnippetText);

    setModel(mSnippetsManager->model());
    setSelectionModel(mSnippetsManager->selectionModel());

    connect(mSnippetsManager->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, [this]() {
        selectionWasChanged();
    });

    connect(mSnippetsManager->model(), &QAbstractItemModel::rowsInserted,
            this, &QTreeView::expandAll);
    connect(mSnippetsManager->model(), &QAbstractItemModel::rowsRemoved,
            this, &QTreeView::expandAll);

    mAddSnippetAction = new QAction(i18n("Add Snippet..."), this);
    mAddSnippetAction->setIcon(QIcon::fromTheme(QStringLiteral("list-add")));
    mEditSnippetAction = new QAction(i18n("Edit Snippet..."), this);
    mEditSnippetAction->setIcon(QIcon::fromTheme(QStringLiteral("document-properties")));
    mDeleteSnippetAction = new QAction(i18n("Remove Snippet"), this);
    mDeleteSnippetAction->setIcon(QIcon::fromTheme(QStringLiteral("edit-delete")));

    mAddSnippetGroupAction = new QAction(i18n("Add Group..."), this);
    mAddSnippetGroupAction->setIcon(QIcon::fromTheme(QStringLiteral("list-add")));
    mEditSnippetGroupAction = new QAction(i18n("Rename Group..."), this);
    mEditSnippetGroupAction->setIcon(QIcon::fromTheme(QStringLiteral("edit-rename")));
    mDeleteSnippetGroupAction = new QAction(i18n("Remove Group"), this);
    mDeleteSnippetGroupAction->setIcon(QIcon::fromTheme(QStringLiteral("edit-delete")));

    connect(mAddSnippetAction, &QAction::triggered, this, [this]() {
        Q_EMIT addSnippet();
    });
    connect(mEditSnippetAction, &QAction::triggered, this, [this]() {
        Q_EMIT editSnippet();
    });
    connect(mAddSnippetGroupAction, &QAction::triggered, this, [this]() {
        Q_EMIT addSnippetGroup();
    });
    connect(mEditSnippetGroupAction, &QAction::triggered, this, [this]() {
        Q_EMIT editSnippetGroup();
    });

    connect(mDeleteSnippetGroupAction, &QAction::triggered, this, [this]() {
        deleteSnippetGroup();
    });
    connect(mDeleteSnippetAction, &QAction::triggered, this, [this]() {
        deleteSnippet();
    });

    expandAll();
    selectionWasChanged();
}

QuicktextWidget::~QuicktextWidget()
{
}

void QuicktextWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu popup;

    const bool itemSelected = mSnippetsManager->selectionModel()->hasSelection();

    bool canAddSnippet = true;
    if (itemSelected) {
        popup.setTitle(mSnippetsManager->selectedName());
        if (mSnippetsManager->snippetGroupSelected()) {
            popup.addAction(mEditSnippetGroupAction);
            popup.addAction(mDeleteSnippetGroupAction);
        } else {
            canAddSnippet = false; // subsnippets are not permitted
            popup.addAction(mAddSnippetAction);
            popup.addAction(mEditSnippetAction);
            popup.addAction(mDeleteSnippetAction);
        }
        popup.addSeparator();
    } else {
        popup.setTitle(i18n("Text Snippets"));
    }
    if (canAddSnippet) {
        popup.addAction(mAddSnippetAction);
    }
    popup.addAction(mAddSnippetGroupAction);

    popup.exec(event->globalPos());
}

void QuicktextWidget::dropEvent(QDropEvent *event)
{
    if (event->source() == this) {
        event->setDropAction(Qt::MoveAction);
    }
    QTreeView::dropEvent(event);
}

QuicktextManager *QuicktextWidget::snippetsManager() const
{
    return mSnippetsManager;
}

void QuicktextWidget::selectionWasChanged()
{
    const bool itemSelected = !mSnippetsManager->selectionModel()->selectedIndexes().isEmpty();

    if (itemSelected) {
        const QModelIndex index = mSnippetsManager->selectionModel()->selectedIndexes().first();
        const bool isGroup = index.data(MailCommon::SnippetsModel::IsGroupRole).toBool();
        if (isGroup) {
            mEditSnippetAction->setEnabled(false);
            mDeleteSnippetAction->setEnabled(false);
            mEditSnippetGroupAction->setEnabled(true);
            mDeleteSnippetGroupAction->setEnabled(true);
        } else {
            mEditSnippetAction->setEnabled(true);
            mDeleteSnippetAction->setEnabled(true);
            mEditSnippetGroupAction->setEnabled(false);
            mDeleteSnippetGroupAction->setEnabled(false);
        }
    } else {
        mEditSnippetAction->setEnabled(false);
        mDeleteSnippetAction->setEnabled(false);
        mEditSnippetGroupAction->setEnabled(false);
        mDeleteSnippetGroupAction->setEnabled(false);
    }
}

void QuicktextWidget::deleteSnippet()
{
    const QModelIndex index = mSnippetsManager->selectionModel()->selectedIndexes().first();

    const QString snippetName = index.data(MailCommon::SnippetsModel::NameRole).toString();

    if (KMessageBox::warningContinueCancel(
            this,
            xi18nc("@info",
                   "Do you really want to remove snippet \"%1\"?<nl/>"
                   "<warning>There is no way to undo the removal.</warning>", snippetName),
            QString(),
            KStandardGuiItem::remove()) == KMessageBox::Cancel) {
        return;
    }

    mSnippetsManager->model()->removeRow(index.row(), mSnippetsManager->currentGroupIndex());
    mSnippetsManager->setDirty(true);
    mSnippetsManager->save();
}

void QuicktextWidget::deleteSnippetGroup()
{
    const QModelIndex groupIndex = mSnippetsManager->currentGroupIndex();
    if (!groupIndex.isValid()) {
        return;
    }

    const QString groupName = groupIndex.data(MailCommon::SnippetsModel::NameRole).toString();

    if (mSnippetsManager->model()->rowCount(groupIndex) > 0) {
        if (KMessageBox::warningContinueCancel(
                this,
                xi18nc("@info",
                       "Do you really want to remove group \"%1\" along with all its snippets?<nl/>"
                       "<warning>There is no way to undo the removal.</warning>", groupName),
                QString(),
                KStandardGuiItem::remove()) == KMessageBox::Cancel) {
            return;
        }
    } else {
        if (KMessageBox::warningContinueCancel(
                nullptr,
                i18nc("@info",
                      "Do you really want to remove group \"%1\"?", groupName),
                QString(),
                KStandardGuiItem::remove()) == KMessageBox::Cancel) {
            return;
        }
    }

    mSnippetsManager->model()->removeRow(groupIndex.row(), QModelIndex());
    mSnippetsManager->setDirty(true);
    mSnippetsManager->save();
}
