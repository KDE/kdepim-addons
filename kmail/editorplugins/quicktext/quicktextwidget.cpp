/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "quicktextwidget.h"
#include "quicktextmanager.h"
#include "quicktexttreewidget.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <MailCommon/SnippetWidget>
#include <MailCommon/SnippetsModel>
#include <QHBoxLayout>
#include <QStackedWidget>

QuickTextWidget::QuickTextWidget(QWidget *parent)
    : QWidget(parent)
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mSnippetsManager = new QuicktextManager(this, this);

    mTreeWidget = new QuicktextTreeWidget(mSnippetsManager, this);
    mTreeWidget->setObjectName(QStringLiteral("treewidget"));
    mainLayout->addWidget(mTreeWidget);

    mStackedWidget = new QStackedWidget(this);
    mStackedWidget->setObjectName(QStringLiteral("stackedwidget"));
    mainLayout->addWidget(mStackedWidget);

    mSnippetWidget = new MailCommon::SnippetWidget(this);
    mSnippetWidget->setObjectName(QStringLiteral("snippetwidget"));
    mStackedWidget->addWidget(mSnippetWidget);

    mEmptyWidget = new QWidget(this);
    mStackedWidget->addWidget(mEmptyWidget);

    connect(mTreeWidget, &QuicktextTreeWidget::addSnippet, this, &QuickTextWidget::addSnippet);
    connect(mTreeWidget, &QuicktextTreeWidget::editSnippet, this, &QuickTextWidget::editSnippet);
    connect(mTreeWidget, &QuicktextTreeWidget::addSnippetGroup, this, &QuickTextWidget::addSnippetGroup);
    connect(mTreeWidget, &QuicktextTreeWidget::editSnippetGroup, this, &QuickTextWidget::editSnippetGroup);
    connect(mSnippetsManager->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]() {
        save();
        if (mSnippetsManager->selectionModel()->selectedIndexes().isEmpty()) {
            mStackedWidget->setCurrentWidget(mEmptyWidget);
            return;
        }
        mStackedWidget->setCurrentWidget(mSnippetWidget);
        const QModelIndex index = mSnippetsManager->selectionModel()->selectedIndexes().first();
        const bool isGroup = index.data(MailCommon::SnippetsModel::IsGroupRole).toBool();
        if (isGroup) {
            editSnippetGroup();
        } else {
            editSnippet();
        }
    });
    mStackedWidget->setCurrentWidget(mEmptyWidget);
}

QuickTextWidget::~QuickTextWidget() = default;

void QuickTextWidget::save()
{
    if (mSnippetWidget->wasChanged()) {
        const int answer = KMessageBox::warningTwoActions(this,
                                                          i18n("QuickText was changed. Do you want to save it?"),
                                                          i18n("Save"),
                                                          KStandardGuiItem::save(),
                                                          KStandardGuiItem::discard());
        if (answer == KMessageBox::ButtonCode::PrimaryAction) {
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
    mStackedWidget->setCurrentWidget(mSnippetWidget);
    mMode = EditMode::AddSnippet;
    mSnippetWidget->clear();
    mSnippetWidget->setGroupSelected(false);
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
    mStackedWidget->setCurrentWidget(mSnippetWidget);
    mMode = EditMode::EditSnippet;
    mSnippetWidget->clear();
    mSnippetWidget->setGroupSelected(false);

    mCurrentGroupIndex = mSnippetsManager->selectionModel()->selectedIndexes().first();
    if (!mCurrentGroupIndex.isValid() || mCurrentGroupIndex.data(MailCommon::SnippetsModel::IsGroupRole).toBool()) {
        return;
    }

    const QModelIndex oldGroupIndex = mSnippetsManager->currentGroupIndex();

    const QString oldSnippetName = mCurrentGroupIndex.data(MailCommon::SnippetsModel::NameRole).toString();
    mSnippetWidget->setGroupModel(mSnippetsManager->model());
    mSnippetWidget->setGroupIndex(oldGroupIndex);
    mSnippetWidget->setName(oldSnippetName);
    mSnippetWidget->setTo(mCurrentGroupIndex.data(MailCommon::SnippetsModel::ToRole).toString());
    mSnippetWidget->setSubject(mCurrentGroupIndex.data(MailCommon::SnippetsModel::SubjectRole).toString());
    mSnippetWidget->setCc(mCurrentGroupIndex.data(MailCommon::SnippetsModel::CcRole).toString());
    mSnippetWidget->setBcc(mCurrentGroupIndex.data(MailCommon::SnippetsModel::BccRole).toString());
    mSnippetWidget->setText(mCurrentGroupIndex.data(MailCommon::SnippetsModel::TextRole).toString());
    mSnippetWidget->setKeyword(mCurrentGroupIndex.data(MailCommon::SnippetsModel::KeywordRole).toString());
    mSnippetWidget->setAttachment(mCurrentGroupIndex.data(MailCommon::SnippetsModel::AttachmentRole).toString());
    mSnippetWidget->setKeySequence(QKeySequence::fromString(mCurrentGroupIndex.data(MailCommon::SnippetsModel::KeySequenceRole).toString()));
    mSnippetWidget->setWasChanged(false);
}

void QuickTextWidget::addSnippetGroup()
{
    mStackedWidget->setCurrentWidget(mSnippetWidget);
    mMode = EditMode::AddGroup;
    mSnippetWidget->clear();
    mSnippetWidget->setGroupSelected(true);
    mSnippetWidget->setWasChanged(false);
}

void QuickTextWidget::editSnippetGroup()
{
    mStackedWidget->setCurrentWidget(mSnippetWidget);
    mMode = EditMode::EditGroup;
    mSnippetWidget->clear();
    mCurrentGroupIndex = mSnippetsManager->currentGroupIndex();
    if (!mCurrentGroupIndex.isValid() || !mCurrentGroupIndex.data(MailCommon::SnippetsModel::IsGroupRole).toBool()) {
        return;
    }
    mSnippetWidget->setGroupSelected(true);
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
    saveModelIndex(index);
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

    saveModelIndex(mCurrentGroupIndex);
}

void QuickTextWidget::saveModelIndex(const QModelIndex &index)
{
    mSnippetsManager->model()->setData(index, mSnippetWidget->name(), MailCommon::SnippetsModel::NameRole);
    mSnippetsManager->model()->setData(index, mSnippetWidget->text(), MailCommon::SnippetsModel::TextRole);
    mSnippetsManager->model()->setData(index, mSnippetWidget->keySequence().toString(), MailCommon::SnippetsModel::KeySequenceRole);
    mSnippetsManager->model()->setData(index, mSnippetWidget->keyword(), MailCommon::SnippetsModel::KeywordRole);
    mSnippetsManager->model()->setData(index, mSnippetWidget->subject(), MailCommon::SnippetsModel::SubjectRole);
    mSnippetsManager->model()->setData(index, mSnippetWidget->cc(), MailCommon::SnippetsModel::CcRole);
    mSnippetsManager->model()->setData(index, mSnippetWidget->bcc(), MailCommon::SnippetsModel::BccRole);
    mSnippetsManager->model()->setData(index, mSnippetWidget->to(), MailCommon::SnippetsModel::ToRole);
    mSnippetsManager->model()->setData(index, mSnippetWidget->attachment(), MailCommon::SnippetsModel::AttachmentRole);

    mSnippetsManager->save();
}

void QuickTextWidget::saveAddGroup()
{
    if (!mSnippetsManager->model()->insertRow(mSnippetsManager->model()->rowCount(), QModelIndex())) {
        return;
    }

    const QModelIndex groupIndex = mSnippetsManager->model()->index(mSnippetsManager->model()->rowCount() - 1, 0, QModelIndex());
    mSnippetsManager->model()->setData(groupIndex, mSnippetWidget->name(), MailCommon::SnippetsModel::NameRole);
    mSnippetsManager->save();
}

void QuickTextWidget::saveEditGroup()
{
    const QString oldGroupName = mCurrentGroupIndex.data(MailCommon::SnippetsModel::NameRole).toString();

    if (oldGroupName == mSnippetWidget->name()) {
        return;
    }

    mSnippetsManager->model()->setData(mCurrentGroupIndex, mSnippetWidget->name(), MailCommon::SnippetsModel::NameRole);
    mSnippetsManager->save();
}

void QuickTextWidget::importQuickText()
{
    mSnippetsManager->importQuickText();
}

void QuickTextWidget::exportQuickText()
{
    mSnippetsManager->exportQuickText();
}
