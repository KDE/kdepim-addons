/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "quicktexttreewidget.h"
#include "quicktextmanager.h"

#include <KLocalizedString>
#include <KMessageBox>

#include <MailCommon/SnippetsModel>
#include <QContextMenuEvent>
#include <QHeaderView>
#include <QMenu>

QuicktextTreeWidget::QuicktextTreeWidget(QuicktextManager *manager, QWidget *parent)
    : QTreeView(parent)
    , mSnippetsManager(manager)
{
    header()->hide();
    setAcceptDrops(true);
    setDragEnabled(true);
    setRootIsDecorated(true);
    setAlternatingRowColors(true);
    connect(mSnippetsManager, &QuicktextManager::insertPlainText, this, &QuicktextTreeWidget::insertSnippetText);

    setModel(mSnippetsManager->model());
    setSelectionModel(mSnippetsManager->selectionModel());

    connect(mSnippetsManager->selectionModel(), &QItemSelectionModel::selectionChanged, this, &QuicktextTreeWidget::selectionWasChanged);

    connect(mSnippetsManager->model(), &QAbstractItemModel::rowsInserted, this, &QTreeView::expandAll);
    connect(mSnippetsManager->model(), &QAbstractItemModel::rowsRemoved, this, &QTreeView::expandAll);

    mAddSnippetAction = new QAction(i18n("Add Snippet…"), this);
    mAddSnippetAction->setIcon(QIcon::fromTheme(QStringLiteral("list-add")));
    mEditSnippetAction = new QAction(i18n("Edit Snippet…"), this);
    mEditSnippetAction->setIcon(QIcon::fromTheme(QStringLiteral("document-properties")));
    mDeleteSnippetAction = new QAction(i18n("Remove Snippet"), this);
    mDeleteSnippetAction->setIcon(QIcon::fromTheme(QStringLiteral("edit-delete")));

    mAddSnippetGroupAction = new QAction(i18n("Add Group…"), this);
    mAddSnippetGroupAction->setIcon(QIcon::fromTheme(QStringLiteral("list-add")));
    mEditSnippetGroupAction = new QAction(i18n("Rename Group…"), this);
    mEditSnippetGroupAction->setIcon(QIcon::fromTheme(QStringLiteral("edit-rename")));
    mDeleteSnippetGroupAction = new QAction(i18n("Remove Group"), this);
    mDeleteSnippetGroupAction->setIcon(QIcon::fromTheme(QStringLiteral("edit-delete")));

    connect(mAddSnippetAction, &QAction::triggered, this, &QuicktextTreeWidget::addSnippet);
    connect(mEditSnippetAction, &QAction::triggered, this, &QuicktextTreeWidget::editSnippet);
    connect(mAddSnippetGroupAction, &QAction::triggered, this, &QuicktextTreeWidget::addSnippetGroup);
    connect(mEditSnippetGroupAction, &QAction::triggered, this, &QuicktextTreeWidget::editSnippetGroup);

    connect(mDeleteSnippetGroupAction, &QAction::triggered, this, &QuicktextTreeWidget::deleteSnippetGroup);
    connect(mDeleteSnippetAction, &QAction::triggered, this, &QuicktextTreeWidget::deleteSnippet);

    expandAll();
    selectionWasChanged();
}

QuicktextTreeWidget::~QuicktextTreeWidget() = default;

void QuicktextTreeWidget::contextMenuEvent(QContextMenuEvent *event)
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

void QuicktextTreeWidget::dropEvent(QDropEvent *event)
{
    if (event->source() == this) {
        event->setDropAction(Qt::MoveAction);
    }
    QTreeView::dropEvent(event);
}

QuicktextManager *QuicktextTreeWidget::snippetsManager() const
{
    return mSnippetsManager;
}

void QuicktextTreeWidget::selectionWasChanged()
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

void QuicktextTreeWidget::deleteSnippet()
{
    const QModelIndex index = mSnippetsManager->selectionModel()->selectedIndexes().first();

    const QString snippetName = index.data(MailCommon::SnippetsModel::NameRole).toString();

    if (KMessageBox::warningContinueCancel(this,
                                           xi18nc("@info",
                                                  "Do you really want to remove snippet \"%1\"?<nl/>"
                                                  "<warning>There is no way to undo the removal.</warning>",
                                                  snippetName),
                                           QString(),
                                           KStandardGuiItem::remove())
        == KMessageBox::Cancel) {
        return;
    }

    mSnippetsManager->model()->removeRow(index.row(), mSnippetsManager->currentGroupIndex());
    mSnippetsManager->save();
}

void QuicktextTreeWidget::deleteSnippetGroup()
{
    const QModelIndex groupIndex = mSnippetsManager->currentGroupIndex();
    if (!groupIndex.isValid()) {
        return;
    }

    const QString groupName = groupIndex.data(MailCommon::SnippetsModel::NameRole).toString();

    if (mSnippetsManager->model()->rowCount(groupIndex) > 0) {
        if (KMessageBox::warningContinueCancel(this,
                                               xi18nc("@info",
                                                      "Do you really want to remove group \"%1\" along with all its snippets?<nl/>"
                                                      "<warning>There is no way to undo the removal.</warning>",
                                                      groupName),
                                               QString(),
                                               KStandardGuiItem::remove())
            == KMessageBox::Cancel) {
            return;
        }
    } else {
        if (KMessageBox::warningContinueCancel(nullptr,
                                               i18nc("@info", "Do you really want to remove group \"%1\"?", groupName),
                                               QString(),
                                               KStandardGuiItem::remove())
            == KMessageBox::Cancel) {
            return;
        }
    }

    mSnippetsManager->model()->removeRow(groupIndex.row(), QModelIndex());
    mSnippetsManager->save();
}

#include "moc_quicktexttreewidget.cpp"
