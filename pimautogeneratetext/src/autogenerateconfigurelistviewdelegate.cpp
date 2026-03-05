/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "autogenerateconfigurelistviewdelegate.h"
#include "autogenerateconfigureaskmodel.h"
#include <QLineEdit>

AutogenerateConfigureListViewDelegate::AutogenerateConfigureListViewDelegate(QObject *parent)
    : QItemDelegate{parent}
{
}

AutogenerateConfigureListViewDelegate::~AutogenerateConfigureListViewDelegate() = default;

QWidget *AutogenerateConfigureListViewDelegate::createEditor(QWidget *parent,
                                                             [[maybe_unused]] const QStyleOptionViewItem &option,
                                                             [[maybe_unused]] const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}

void AutogenerateConfigureListViewDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
    if (lineEdit) {
        const QString text = index.data(AutogenerateConfigureAskModel::TitleRole).toString();
        lineEdit->setText(text);
    }
}

void AutogenerateConfigureListViewDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
    if (lineEdit) {
        model->setData(index, lineEdit->text(), AutogenerateConfigureAskModel::TitleRole);
    }
}

void AutogenerateConfigureListViewDelegate::updateEditorGeometry(QWidget *editor,
                                                                 const QStyleOptionViewItem &option,
                                                                 [[maybe_unused]] const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

#include "moc_autogenerateconfigurelistviewdelegate.cpp"
