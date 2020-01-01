/*
   Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

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
#include <KSharedConfig>
#include <MailCommon/SnippetsModel>

#include <KLocalizedString>
#include <QFileDialog>
#include <QIcon>
#include <QTextEdit>

#include <QAction>
#include <QPointer>
#include <QItemSelectionModel>
#include <QDebug>

class QuicktextManager::Private
{
public:
    Private(QuicktextManager *qq, QWidget *parentWidget)
        : q(qq)
        , mParent(parentWidget)
    {
    }

    QModelIndex currentGroupIndex() const;

    void save();

    QuicktextManager *q = nullptr;
    MailCommon::SnippetsModel *mModel = nullptr;
    QItemSelectionModel *mSelectionModel = nullptr;
    QWidget *mParent = nullptr;
};

QModelIndex QuicktextManager::Private::currentGroupIndex() const
{
    if (mSelectionModel->selectedIndexes().isEmpty()) {
        return QModelIndex();
    }

    const QModelIndex index = mSelectionModel->selectedIndexes().first();
    if (index.data(MailCommon::SnippetsModel::IsGroupRole).toBool()) {
        return index;
    } else {
        return mModel->parent(index);
    }
}

void QuicktextManager::Private::save()
{
    MailCommon::SnippetsModel::instance()->save();
}

QuicktextManager::QuicktextManager(QObject *parent, QWidget *parentWidget)
    : QObject(parent)
    , d(new Private(this, parentWidget))
{
    d->mModel = MailCommon::SnippetsModel::instance();
    d->mSelectionModel = new QItemSelectionModel(d->mModel);
}

QuicktextManager::~QuicktextManager()
{
    d->save();
    delete d;
}

QAbstractItemModel *QuicktextManager::model() const
{
    return d->mModel;
}

QItemSelectionModel *QuicktextManager::selectionModel() const
{
    return d->mSelectionModel;
}

bool QuicktextManager::snippetGroupSelected() const
{
    if (d->mSelectionModel->selectedIndexes().isEmpty()) {
        return false;
    }

    return d->mSelectionModel->selectedIndexes().first().data(MailCommon::SnippetsModel::IsGroupRole).toBool();
}

QString QuicktextManager::selectedName() const
{
    if (d->mSelectionModel->selectedIndexes().isEmpty()) {
        return QString();
    }

    return d->mSelectionModel->selectedIndexes().first().data(MailCommon::SnippetsModel::NameRole).toString();
}

void QuicktextManager::save()
{
    d->save();
}

QModelIndex QuicktextManager::currentGroupIndex() const
{
    return d->currentGroupIndex();
}

void QuicktextManager::importQuickText()
{
    const QString filename = QFileDialog::getOpenFileName(d->mParent, i18n("Import QuickText"));
    if (!filename.isEmpty()) {
        d->mModel->load(filename);
    }
}

void QuicktextManager::exportQuickText()
{
    const QString filename = QFileDialog::getSaveFileName(d->mParent, i18n("Export QuickText"));
    if (!filename.isEmpty()) {
        d->mModel->save(filename);
    }
}

#include "moc_quicktextmanager.cpp"
