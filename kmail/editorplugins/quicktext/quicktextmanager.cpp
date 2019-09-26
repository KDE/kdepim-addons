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
#include <KSharedConfig>
#include <MailCommon/SnippetsModel>

#include <KLocalizedString>
#include <KMessageBox>
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

    void dndDone();

    void slotAddNewDndSnippset(const QString &);

    void save();

    QuicktextManager *q = nullptr;
    MailCommon::SnippetsModel *mModel = nullptr;
    QItemSelectionModel *mSelectionModel = nullptr;
    QWidget *mParent = nullptr;
    bool mDirty = false;
};

QModelIndex QuicktextManager::Private::currentGroupIndex() const
{
    qDebug() << mSelectionModel->selectedIndexes();
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

#if 0
void QuicktextManager::Private::createSnippet(const QString &text)
{
    const bool noGroupAvailable = (mModel->rowCount() == 0);

    if (noGroupAvailable) {
        // create a 'General' snippet group
        if (!mModel->insertRow(mModel->rowCount(), QModelIndex())) {
            return;
        }

        const QModelIndex groupIndex = mModel->index(mModel->rowCount() - 1, 0, QModelIndex());
        mModel->setData(groupIndex, i18n("General"), MailCommon::SnippetsModel::NameRole);

        mSelectionModel->select(groupIndex, QItemSelectionModel::ClearAndSelect);
    }

    QPointer<SnippetDialog> dlg = new SnippetDialog(mActionCollection, false, mParent);
    dlg->setWindowTitle(i18nc("@title:window", "Add Snippet"));
    dlg->setGroupModel(mModel);
    dlg->setGroupIndex(currentGroupIndex());
    dlg->setText(text);

    if (dlg->exec()) {
        const QModelIndex groupIndex = dlg->groupIndex();

        if (!mModel->insertRow(mModel->rowCount(groupIndex), groupIndex)) {
            delete dlg;
            return;
        }

        const QModelIndex index = mModel->index(mModel->rowCount(groupIndex) - 1, 0, groupIndex);
        mModel->setData(index, dlg->name(), MailCommon::SnippetsModel::NameRole);
        mModel->setData(index, dlg->text(), MailCommon::SnippetsModel::TextRole);
        mModel->setData(index, dlg->keySequence().toString(), MailCommon::SnippetsModel::KeySequenceRole);
        mModel->setData(index, dlg->keyword(), MailCommon::SnippetsModel::KeywordRole);

        Q_EMIT mModel->updateActionCollection(QString(), dlg->name(), dlg->keySequence(), dlg->text());
        mDirty = true;
        save();
    }
    delete dlg;
}
#endif

void QuicktextManager::Private::slotAddNewDndSnippset(const QString &text)
{
}

void QuicktextManager::Private::dndDone()
{
    mDirty = true;
}
#if 0
void QuicktextManager::Private::editSnippet()
{
    QModelIndex index = mSelectionModel->selectedIndexes().first();
    if (!index.isValid() || index.data(MailCommon::SnippetsModel::IsGroupRole).toBool()) {
        return;
    }

    const QModelIndex oldGroupIndex = currentGroupIndex();

    const QString oldSnippetName = index.data(MailCommon::SnippetsModel::NameRole).toString();
    QPointer<SnippetDialog> dlg = new SnippetDialog(mActionCollection, false, mParent);
    dlg->setWindowTitle(i18nc("@title:window", "Edit Snippet"));
    dlg->setGroupModel(mModel);
    dlg->setGroupIndex(oldGroupIndex);
    dlg->setName(oldSnippetName);
    dlg->setText(index.data(MailCommon::SnippetsModel::TextRole).toString());
    dlg->setKeyword(index.data(MailCommon::SnippetsModel::KeywordRole).toString());
    dlg->setKeySequence(
        QKeySequence::fromString(
            index.data(MailCommon::SnippetsModel::KeySequenceRole).toString()));

    if (dlg->exec()) {
        const QModelIndex newGroupIndex = dlg->groupIndex();

        if (oldGroupIndex != newGroupIndex) {
            mModel->removeRow(index.row(), oldGroupIndex);
            mModel->insertRow(mModel->rowCount(newGroupIndex), newGroupIndex);

            index = mModel->index(mModel->rowCount(newGroupIndex) - 1, 0, newGroupIndex);
        }

        mModel->setData(index, dlg->name(), MailCommon::SnippetsModel::NameRole);
        mModel->setData(index, dlg->text(), MailCommon::SnippetsModel::TextRole);
        mModel->setData(index, dlg->keySequence().toString(), MailCommon::SnippetsModel::KeySequenceRole);
        mModel->setData(index, dlg->keyword(), MailCommon::SnippetsModel::KeywordRole);

        Q_EMIT mModel->updateActionCollection(oldSnippetName, dlg->name(), dlg->keySequence(), dlg->text());
        mDirty = true;
        save();
    }
    delete dlg;
}

void QuicktextManager::Private::addSnippetGroup()
{
    QPointer<SnippetDialog> dlg = new SnippetDialog(mActionCollection, true, mParent);
    dlg->setWindowTitle(i18nc("@title:window", "Add Group"));

    if (dlg->exec()) {
        if (!mModel->insertRow(mModel->rowCount(), QModelIndex())) {
            qCDebug(MAILCOMMON_LOG) << "unable to insert row";
            delete dlg;
            return;
        }

        const QModelIndex groupIndex = mModel->index(mModel->rowCount() - 1, 0, QModelIndex());
        mModel->setData(groupIndex, dlg->name(), MailCommon::SnippetsModel::NameRole);
        mDirty = true;
        save();
    }
    delete dlg;
}

void QuicktextManager::Private::editSnippetGroup()
{
    const QModelIndex groupIndex = currentGroupIndex();
    if (!groupIndex.isValid() || !groupIndex.data(MailCommon::SnippetsModel::IsGroupRole).toBool()) {
        return;
    }
#if 0
    QPointer<SnippetDialog> dlg = new SnippetDialog(mActionCollection, true, mParent);
    dlg->setWindowTitle(i18nc("@title:window", "Edit Group"));
    const QString oldGroupName = groupIndex.data(MailCommon::SnippetsModel::NameRole).toString();
    dlg->setName(oldGroupName);

    if (dlg->exec()) {
        if (oldGroupName == dlg->name()) {
            delete dlg;
            return;
        }

        mModel->setData(groupIndex, dlg->name(), MailCommon::SnippetsModel::NameRole);
        mDirty = true;
        save();
    }
    delete dlg;
#endif
}
#endif

void QuicktextManager::Private::save()
{
    if (!mDirty) {
        return;
    }

    MailCommon::SnippetsModel::instance()->save();
    mDirty = false;
}

QuicktextManager::QuicktextManager(QObject *parent, QWidget *parentWidget)
    : QObject(parent)
    , d(new Private(this, parentWidget))
{
    d->mModel = MailCommon::SnippetsModel::instance();
    d->mSelectionModel = new QItemSelectionModel(d->mModel);

    connect(d->mModel, &MailCommon::SnippetsModel::dndDone, this, [this]() {
        d->dndDone();
    });
    connect(d->mModel, &MailCommon::SnippetsModel::addNewDndSnippset, this, [this](const QString &str) {
        d->slotAddNewDndSnippset(str);
    });
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

void QuicktextManager::setDirty(bool b)
{
    d->mDirty = b;
}

#include "moc_quicktextmanager.cpp"
