/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "quicktextmanager.h"
#include <KSharedConfig>
#include <MailCommon/SnippetsModel>

#include <KLocalizedString>
#include <QFileDialog>

#include <QItemSelectionModel>

QModelIndex QuicktextManager::currentGroupIndex() const
{
    if (mSelectionModel->selectedIndexes().isEmpty()) {
        return {};
    }

    const QModelIndex index = mSelectionModel->selectedIndexes().first();
    if (index.data(MailCommon::SnippetsModel::IsGroupRole).toBool()) {
        return index;
    } else {
        return mModel->parent(index);
    }
}

void QuicktextManager::save()
{
    MailCommon::SnippetsModel::instance()->save();
}

QuicktextManager::QuicktextManager(QObject *parent, QWidget *parentWidget)
    : QObject(parent)
    , mParent(parentWidget)
{
    mModel = MailCommon::SnippetsModel::instance();
    mSelectionModel = new QItemSelectionModel(mModel);
}

QuicktextManager::~QuicktextManager()
{
    save();
}

QAbstractItemModel *QuicktextManager::model() const
{
    return mModel;
}

QItemSelectionModel *QuicktextManager::selectionModel() const
{
    return mSelectionModel;
}

bool QuicktextManager::snippetGroupSelected() const
{
    if (mSelectionModel->selectedIndexes().isEmpty()) {
        return false;
    }

    return mSelectionModel->selectedIndexes().first().data(MailCommon::SnippetsModel::IsGroupRole).toBool();
}

QString QuicktextManager::selectedName() const
{
    if (mSelectionModel->selectedIndexes().isEmpty()) {
        return {};
    }

    return mSelectionModel->selectedIndexes().first().data(MailCommon::SnippetsModel::NameRole).toString();
}

void QuicktextManager::importQuickText()
{
    const QString filename = QFileDialog::getOpenFileName(mParent, i18n("Import QuickText"));
    if (!filename.isEmpty()) {
        mModel->load(filename);
    }
}

void QuicktextManager::exportQuickText()
{
    const QString filename = QFileDialog::getSaveFileName(mParent, i18n("Export QuickText"));
    if (!filename.isEmpty()) {
        mModel->save(filename);
    }
}

#include "moc_quicktextmanager.cpp"
