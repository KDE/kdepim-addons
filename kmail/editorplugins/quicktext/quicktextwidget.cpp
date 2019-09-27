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
#include "quicktextmanager.h"
#include "quicktexttreewidget.h"
#include "quicktextwidget.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <MailCommon/SnippetWidget>
#include <MailCommon/SnippetsModel>
#include <QDebug>
#include <KMessageBox>

QuickTextWidget::QuickTextWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mSnippetsManager = new QuicktextManager(this, this);

    mTreeWidget = new QuicktextTreeWidget(mSnippetsManager, this);
    mTreeWidget->setObjectName(QStringLiteral("treewidget"));
    mainLayout->addWidget(mTreeWidget);

    mSnippetWidget = new MailCommon::SnippetWidget(this);
    mSnippetWidget->setObjectName(QStringLiteral("snippetwidget"));
    mainLayout->addWidget(mSnippetWidget);
    connect(mTreeWidget, &QuicktextTreeWidget::addSnippet, this, &QuickTextWidget::addSnippet);
    connect(mTreeWidget, &QuicktextTreeWidget::editSnippet, this, &QuickTextWidget::editSnippet);
    connect(mTreeWidget, &QuicktextTreeWidget::addSnippetGroup, this, &QuickTextWidget::addSnippetGroup);
    connect(mTreeWidget, &QuicktextTreeWidget::editSnippetGroup, this, &QuickTextWidget::editSnippetGroup);
    connect(mSnippetsManager->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, [this]() {
        save();
        if (mSnippetsManager->selectionModel()->selectedIndexes().isEmpty()) {
            return;
        }
        const QModelIndex index = mSnippetsManager->selectionModel()->selectedIndexes().first();
        const bool isGroup = index.data(MailCommon::SnippetsModel::IsGroupRole).toBool();
        if (isGroup) {
            editSnippetGroup();
        } else {
            editSnippet();
        }
    });
}

QuickTextWidget::~QuickTextWidget()
{
}

void QuickTextWidget::save()
{
    if (mSnippetWidget->wasChanged()) {
        if (KMessageBox::Yes == KMessageBox::warningYesNo(this, i18n("QuickText was changed. Do you want to save it?"), i18n("Save"))) {
            switch (mMode) {
            case EditMode::AddSnippet:
                saveAddSnippet();
                break;
            case EditMode::EditSnippet:
                saveEditSnippet();
                break;
            case EditMode::AddGroup:
                saveAddGroup();
                break;
            case EditMode::EditGroup:
                saveEditGroup();
                break;
            case EditMode::Unknown:
                break;
            }
        }
    }
    mMode = EditMode::Unknown;
    mSnippetWidget->clear();
    mSnippetWidget->setWasChanged(false);
}

void QuickTextWidget::addSnippet()
{
    mMode = EditMode::AddSnippet;
    mSnippetWidget->clear();
    const bool noGroupAvailable = (mSnippetsManager->model()->rowCount() == 0);

    if (noGroupAvailable) {
        // create a 'General' snippet group
        if (!mSnippetsManager->model()->insertRow(mSnippetsManager->model()->rowCount(), QModelIndex())) {
            return;
        }

        const QModelIndex groupIndex = mSnippetsManager->model()->index(mSnippetsManager->model()->rowCount() - 1, 0, QModelIndex());
        mSnippetsManager->model()->setData(groupIndex, i18n("General"), MailCommon::SnippetsModel::NameRole);

        mSnippetsManager->selectionModel()->select(groupIndex, QItemSelectionModel::ClearAndSelect);
        mSnippetWidget->setGroupIndex(mSnippetsManager->currentGroupIndex());
        mSnippetWidget->setText(QString());
    }
    mSnippetWidget->setGroupModel(mSnippetsManager->model());
    mSnippetWidget->setWasChanged(false);
}

void QuickTextWidget::editSnippet()
{
    mMode = EditMode::EditSnippet;
    mSnippetWidget->clear();

    mCurrentGroupIndex = mSnippetsManager->selectionModel()->selectedIndexes().first();
    if (!mCurrentGroupIndex.isValid() || mCurrentGroupIndex.data(MailCommon::SnippetsModel::IsGroupRole).toBool()) {
        return;
    }

    const QModelIndex oldGroupIndex = mSnippetsManager->currentGroupIndex();

    const QString oldSnippetName = mCurrentGroupIndex.data(MailCommon::SnippetsModel::NameRole).toString();
    mSnippetWidget->setGroupModel(mSnippetsManager->model());
    mSnippetWidget->setGroupIndex(oldGroupIndex);
    mSnippetWidget->setName(oldSnippetName);
    mSnippetWidget->setText(mCurrentGroupIndex.data(MailCommon::SnippetsModel::TextRole).toString());
    mSnippetWidget->setKeyword(mCurrentGroupIndex.data(MailCommon::SnippetsModel::KeywordRole).toString());
    mSnippetWidget->setKeySequence(
                QKeySequence::fromString(
                    mCurrentGroupIndex.data(MailCommon::SnippetsModel::KeySequenceRole).toString()));
    mSnippetWidget->setWasChanged(false);
}

void QuickTextWidget::addSnippetGroup()
{
    mMode = EditMode::AddGroup;
    mSnippetWidget->clear();
    mSnippetWidget->setWasChanged(false);
}

void QuickTextWidget::editSnippetGroup()
{
    mMode = EditMode::EditGroup;
    mSnippetWidget->clear();
    mCurrentGroupIndex = mSnippetsManager->currentGroupIndex();
    if (!mCurrentGroupIndex.isValid() || !mCurrentGroupIndex.data(MailCommon::SnippetsModel::IsGroupRole).toBool()) {
        return;
    }
    const QString oldGroupName = mCurrentGroupIndex.data(MailCommon::SnippetsModel::NameRole).toString();
    mSnippetWidget->setName(oldGroupName);
    mSnippetWidget->setWasChanged(false);
}

void QuickTextWidget::saveAddSnippet()
{
    const QModelIndex groupIndex = mSnippetWidget->groupIndex();

    if (!mSnippetsManager->model()->insertRow(mSnippetsManager->model()->rowCount(groupIndex), groupIndex)) {
        return;
    }

    const QModelIndex index = mSnippetsManager->model()->index(mSnippetsManager->model()->rowCount(groupIndex) - 1, 0, groupIndex);
    mSnippetsManager->model()->setData(index, mSnippetWidget->name(), MailCommon::SnippetsModel::NameRole);
    mSnippetsManager->model()->setData(index, mSnippetWidget->text(), MailCommon::SnippetsModel::TextRole);
    mSnippetsManager->model()->setData(index, mSnippetWidget->keySequence().toString(), MailCommon::SnippetsModel::KeySequenceRole);
    mSnippetsManager->model()->setData(index, mSnippetWidget->keyword(), MailCommon::SnippetsModel::KeywordRole);
    mSnippetsManager->setDirty(true);
    mSnippetsManager->save();
}

void QuickTextWidget::saveEditSnippet()
{
    const QModelIndex newGroupIndex = mSnippetWidget->groupIndex();
    const QModelIndex oldGroupIndex = mSnippetsManager->currentGroupIndex();

    if (oldGroupIndex != newGroupIndex) {
        mSnippetsManager->model()->removeRow(mCurrentGroupIndex.row(), oldGroupIndex);
        mSnippetsManager->model()->insertRow(mSnippetsManager->model()->rowCount(newGroupIndex), newGroupIndex);

        mCurrentGroupIndex = mSnippetsManager->model()->index(mSnippetsManager->model()->rowCount(newGroupIndex) - 1, 0, newGroupIndex);
    }

    mSnippetsManager->model()->setData(mCurrentGroupIndex, mSnippetWidget->name(), MailCommon::SnippetsModel::NameRole);
    mSnippetsManager->model()->setData(mCurrentGroupIndex, mSnippetWidget->text(), MailCommon::SnippetsModel::TextRole);
    mSnippetsManager->model()->setData(mCurrentGroupIndex, mSnippetWidget->keySequence().toString(), MailCommon::SnippetsModel::KeySequenceRole);
    mSnippetsManager->model()->setData(mCurrentGroupIndex, mSnippetWidget->keyword(), MailCommon::SnippetsModel::KeywordRole);
    mSnippetsManager->setDirty(true);
    mSnippetsManager->save();

}

void QuickTextWidget::saveAddGroup()
{
    if (!mSnippetsManager->model()->insertRow(mSnippetsManager->model()->rowCount(), QModelIndex())) {
        return;
    }

    const QModelIndex groupIndex = mSnippetsManager->model()->index(mSnippetsManager->model()->rowCount() - 1, 0, QModelIndex());
    mSnippetsManager->model()->setData(groupIndex, mSnippetWidget->name(), MailCommon::SnippetsModel::NameRole);
    mSnippetsManager->setDirty(true);
    mSnippetsManager->save();
}

void QuickTextWidget::saveEditGroup()
{
    const QString oldGroupName = mCurrentGroupIndex.data(MailCommon::SnippetsModel::NameRole).toString();

    if (oldGroupName == mSnippetWidget->name()) {
        return;
    }

    mSnippetsManager->model()->setData(mCurrentGroupIndex, mSnippetWidget->name(), MailCommon::SnippetsModel::NameRole);
    mSnippetsManager->setDirty(true);
    mSnippetsManager->save();
}
