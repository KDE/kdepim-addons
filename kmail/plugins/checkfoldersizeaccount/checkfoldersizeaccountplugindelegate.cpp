/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "checkfoldersizeaccountplugindelegate.h"
#include <Akonadi/Collection>
#include <Akonadi/CollectionStatistics>
#include <Akonadi/EntityTreeModel>
#include <KFormat>
#include <QPainter>
#include <QTreeView>
CheckFolderSizeAccountPluginDelegate::CheckFolderSizeAccountPluginDelegate(QTreeView *view, QObject *parent)
    : QStyledItemDelegate{parent}
    , mTreeView(view)
{
}

CheckFolderSizeAccountPluginDelegate::~CheckFolderSizeAccountPluginDelegate() = default;

void CheckFolderSizeAccountPluginDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    // Now, we retrieve the correct style option by calling initStyleOption from
    // the superclass.
    QStyleOptionViewItem option4 = option;
    QStyledItemDelegate::initStyleOption(&option4, index);
    QString text = option4.text;

    // Now calculate the rectangle for the text
    QStyle *s = mTreeView->style();
    const QWidget *widget = option4.widget;
    const QRect textRect = s->subElementRect(QStyle::SE_ItemViewItemText, &option4, widget);

    // When checking if the item is expanded, we need to check that for the first
    // column, as Qt only recognizes the index as expanded for the first column
    const QModelIndex firstColumn = index.sibling(index.row(), 0);
    auto collection = firstColumn.data(Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();

    if (!collection.isValid()) {
        qCritical() << "Invalid collection at index" << firstColumn << firstColumn.data().toString() << "sibling of" << index
                    << "rowCount=" << index.model()->rowCount(index.parent()) << "parent=" << index.parent().data().toString();
        return;
    }

    const Akonadi::CollectionStatistics statistics = collection.statistics();

    KFormat format;
    painter->drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, QStringLiteral("%1").arg(format.formatByteSize(qMax(0LL, statistics.size()))));
}

#include "moc_checkfoldersizeaccountplugindelegate.cpp"
