/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingwidget.h"
#include "confirmbeforedeletingcreateruledialog.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QIcon>
#include <QMenu>
#include <QPointer>
#include <QTreeWidget>
#include <QVBoxLayout>

ConfirmBeforeDeletingWidget::ConfirmBeforeDeletingWidget(QWidget *parent)
    : QWidget(parent)
    , mTreeWidget(new QTreeWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    // TODO
    mainLayout->addWidget(mTreeWidget);
    mTreeWidget->setAlternatingRowColors(true);
    mTreeWidget->setRootIsDecorated(false);
    mTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    const QStringList lst = {i18n("Name"), i18n("Type")};
    mTreeWidget->setHeaderLabels(lst);
    connect(mTreeWidget, &QTreeWidget::customContextMenuRequested, this, &ConfirmBeforeDeletingWidget::slotCustomContextMenuRequested);
    fillRules();
}

ConfirmBeforeDeletingWidget::~ConfirmBeforeDeletingWidget()
{
}

void ConfirmBeforeDeletingWidget::fillRules()
{
    // TODO
}

void ConfirmBeforeDeletingWidget::slotEditRule()
{
    // TODO
}

void ConfirmBeforeDeletingWidget::slotCustomContextMenuRequested(const QPoint &p)
{
    QMenu menu(this);
    menu.addAction(QIcon::fromTheme(QStringLiteral("document-open")), i18n("Add Rule..."), this, &ConfirmBeforeDeletingWidget::slotAddRule);
    QTreeWidgetItem *item = mTreeWidget->currentItem();
    if (item) {
        menu.addAction(QIcon::fromTheme(QStringLiteral("document-open")), i18n("Open"), this, &ConfirmBeforeDeletingWidget::slotEditRule);
        menu.addSeparator();
        menu.addAction(QIcon::fromTheme(QStringLiteral("edit-delete")), i18n("Remove filter"), this, &ConfirmBeforeDeletingWidget::slotRemoveRule);
    }
    menu.exec(QCursor::pos());
}

void ConfirmBeforeDeletingWidget::slotRemoveRule()
{
    QTreeWidgetItem *item = mTreeWidget->currentItem();
    if (item) {
        if (KMessageBox::questionYesNo(this, i18n("Do you want to remove this rule?"), i18n("Remove Rule")) == KMessageBox::Yes) {
            delete item;
        }
    }
}

void ConfirmBeforeDeletingWidget::slotAddRule()
{
    QPointer<ConfirmBeforeDeletingCreateRuleDialog> dlg = new ConfirmBeforeDeletingCreateRuleDialog(this);
    if (dlg->exec()) {
        const ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo info = dlg->info();

        // TODO save it.
    }
    delete dlg;
}

void ConfirmBeforeDeletingWidget::save()
{
}
