/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>
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
#include "selectitemfolderjob.h"
#include "selectimapfoldermodel.h"
#include "imapfoldercompletionplugin_debug.h"
#include <QHBoxLayout>
#include <QTreeView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QLineEdit>
#include <QPainter>
#include <QInputDialog>

#include <KLocalizedString>

#include <KSieveUi/SieveImapAccountSettings>

SearchFilterProxyModel::SearchFilterProxyModel(QObject *parent)
    : KRecursiveFilterProxyModel(parent)
{

}

void SearchFilterProxyModel::setSearchPattern(const QString &pattern)
{
    if (mPattern != pattern) {
        mPattern = pattern;
        invalidate();
    }
}

bool SearchFilterProxyModel::acceptRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex sourceIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    if (!mPattern.isEmpty()) {
        const QString text = sourceIndex.data(Qt::DisplayRole).toString();
        return text.contains(mPattern, Qt::CaseInsensitive);
    } else {
        return true;
    }
}

SelectImapFolderWidget::SelectImapFolderWidget(const KSieveUi::SieveImapAccountSettings &account, QWidget *parent)
    : QWidget(parent)
{
    mModel = SelectImapFolderModel::self()->folderModel(account);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);

    mSearchLineEdit = new QLineEdit(this);
    mSearchLineEdit->setObjectName(QStringLiteral("searchline"));
    mSearchLineEdit->setClearButtonEnabled(true);
    mSearchLineEdit->setPlaceholderText(i18n("Search..."));
    mainLayout->addWidget(mSearchLineEdit);

    mTreeView = new SelectImapFolderTreeView(this);
    mTreeView->setObjectName(QStringLiteral("treeview"));
    mTreeView->header()->hide();

    mFilter = new SearchFilterProxyModel(this);
    mFilter->setSourceModel(mModel);

    mTreeView->setModel(mFilter);
    connect(mTreeView, &QTreeView::doubleClicked, this, &SelectImapFolderWidget::slotDoubleClicked);
    mainLayout->addWidget(mTreeView);

    connect(mSearchLineEdit, &QLineEdit::textChanged, this, &SelectImapFolderWidget::slotSearchPattern);
}

SelectImapFolderWidget::~SelectImapFolderWidget()
{

}

void SelectImapFolderWidget::slotSearchPattern(const QString &pattern)
{
    mTreeView->expandAll();
    mFilter->setSearchPattern(pattern);
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
        const QString name = QInputDialog::getText(this, i18n("Create Folder"), i18n("Folder Name:"));
        if (!name.trimmed().isEmpty()) {
            //TODO more check for folder name ?
            //TODO create it
            SelectImapFolderModel::self()->createNewFolder(name);
        }
    }
}

SelectImapFolderTreeView::SelectImapFolderTreeView(QWidget *parent)
    : QTreeView(parent)
{

}

SelectImapFolderTreeView::~SelectImapFolderTreeView()
{

}

void SelectImapFolderTreeView::generalPaletteChanged()
{
    const QPalette palette = viewport()->palette();
    QColor color = palette.text().color();
    color.setAlpha(128);
    mTextColor = color;
}

void SelectImapFolderTreeView::paintEvent(QPaintEvent *event)
{
    if (!model() || model()->rowCount() == 0) {
        QPainter p(viewport());

        QFont font = p.font();
        font.setItalic(true);
        p.setFont(font);

        if (!mTextColor.isValid()) {
            generalPaletteChanged();
        }
        p.setPen(mTextColor);

        p.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, i18n("Unable to load folder list"));
    } else {
        QTreeView::paintEvent(event);
    }
}

