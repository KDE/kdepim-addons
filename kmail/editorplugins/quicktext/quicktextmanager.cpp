/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

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
    const auto selectedIndexes = mSelectionModel->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        return {};
    }

    const QModelIndex index = selectedIndexes.constFirst();
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
    mSelectionModel = new QItemSelectionModel(mModel, this);
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
    const auto selectedIndexes = mSelectionModel->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        return false;
    }

    return selectedIndexes.constFirst().data(MailCommon::SnippetsModel::IsGroupRole).toBool();
}

QString QuicktextManager::selectedName() const
{
    const auto selectedIndexes = mSelectionModel->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        return {};
    }

    return selectedIndexes.constFirst().data(MailCommon::SnippetsModel::NameRole).toString();
}

void QuicktextManager::importQuickText()
{
    const QString filename = QFileDialog::getOpenFileName(mParent, i18nc("@title:window", "Import QuickText"));
    if (!filename.isEmpty()) {
        mModel->load(filename);
    }
}

void QuicktextManager::exportQuickText()
{
    const QString filename = QFileDialog::getSaveFileName(mParent, i18nc("@title:window", "Export QuickText"));
    if (!filename.isEmpty()) {
        mModel->save(filename);
    }
}

#include "moc_quicktextmanager.cpp"
