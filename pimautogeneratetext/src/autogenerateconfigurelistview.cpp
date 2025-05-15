/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "autogenerateconfigurelistview.h"
#include "autogenerateconfigureaskmodel.h"
#include "autogenerateconfigurelistviewdelegate.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QContextMenuEvent>
#include <QMenu>
#include <QSortFilterProxyModel>
AutogenerateConfigureListView::AutogenerateConfigureListView(QWidget *parent)
    : QListView(parent)
    , mModel(new AutogenerateConfigureAskModel(this))
    , mSortFilterProxyModel(new QSortFilterProxyModel(this))
{
    mSortFilterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    mSortFilterProxyModel->setSourceModel(mModel);
    setModel(mSortFilterProxyModel);
    setItemDelegate(new AutogenerateConfigureListViewDelegate(this));
}

AutogenerateConfigureListView::~AutogenerateConfigureListView() = default;

void AutogenerateConfigureListView::setFilterText(const QString &str)
{
    mSortFilterProxyModel->setFilterFixedString(str);
}

QList<AutogenerateConfigureAskInfo> AutogenerateConfigureListView::askInfos() const
{
    return mModel->askInfos();
}

void AutogenerateConfigureListView::setAskInfos(const QList<AutogenerateConfigureAskInfo> &newAskItems)
{
    mModel->setAskInfos(newAskItems);
}

void AutogenerateConfigureListView::setData(const QModelIndex &current, const QString &text)
{
    if (!mModel->setData(current, text, AutogenerateConfigureAskModel::TextRole)) {
        qWarning() << " Impossible to change text";
    }
}

void AutogenerateConfigureListView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    auto addAction = new QAction(QIcon::fromTheme(QStringLiteral("document-edit")), i18nc("@action", "Add…"), &menu);
    connect(addAction, &QAction::triggered, this, [this]() {
        AutogenerateConfigureAskInfo info;
        info.setTitle(i18n("Ask to AI"));
        mModel->addItem(std::move(info));
    });
    menu.addAction(addAction);
    const QModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        auto editAction = new QAction(QIcon::fromTheme(QStringLiteral("document-edit")), i18nc("@action", "Modify…"), &menu);
        connect(editAction, &QAction::triggered, this, [index, this]() {
            edit(index);
        });
        menu.addAction(editAction);

        menu.addSeparator();
        auto removeAction = new QAction(QIcon::fromTheme(QStringLiteral("list-remove")), i18nc("@action", "Remove…"), &menu);
        connect(removeAction, &QAction::triggered, this, [index, this]() {
            if (KMessageBox::warningTwoActions(this,
                                               i18n("Do you want to remove it?"),
                                               i18nc("@title", "Remove"),
                                               KStandardGuiItem::remove(),
                                               KStandardGuiItem::cancel())
                == KMessageBox::PrimaryAction) {
                mModel->removeItem(index.row());
            }
        });
        menu.addAction(removeAction);
    }
    if (!menu.actions().isEmpty()) {
        menu.exec(event->globalPos());
    }
}

#include "moc_autogenerateconfigurelistview.cpp"
